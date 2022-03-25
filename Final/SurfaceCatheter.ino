#include <TRSim_Blue.h>

// Set up events
typedef struct _eventDetails {
  char value;
  const char* description;
  uint32_t color;
} EventDetails;
EventDetails events[] = {
  {TRSim_Blue::EVENT_PAYLOAD_POWER_ON, "Payload Power On", 0xff0000},
  {TRSim_Blue::EVENT_ESCAPE_ENABLED, "Escape Enabled", 0x00ff00},
  {TRSim_Blue::EVENT_ESCAPE_CMD, "Escape Commanded", 0x0000ff},
  {TRSim_Blue::EVENT_LIFTOFF, "Liftoff", 0xffff00},
  {TRSim_Blue::EVENT_MECO, "MECO - Main Engine Cut Off", 0xff00ff},
  {TRSim_Blue::EVENT_SEPARATION, "Capsule Separation", 0x00ffff},
  {TRSim_Blue::EVENT_COAST_START, "Coast Start", 0xff7777},
  {TRSim_Blue::EVENT_APOGEE, "Apogee", 0x7777ff},
  {TRSim_Blue::EVENT_COAST_END, "Coast End", 0x77ff77},
  {TRSim_Blue::EVENT_DROGUE, "Drogue Deployed", 0x777777},
  {TRSim_Blue::EVENT_MAIN, "Main Chutes Deployed", 0x33ffff},
  {TRSim_Blue::EVENT_TOUCHDOWN, "Touchdown", 0xff33ff},
  {TRSim_Blue::EVENT_SAFING, "Safing", 0xffff33},
  {TRSim_Blue::EVENT_MISSION_END, "Mission End", 0x333333}
};

// Set up Simulator
TRSim_Blue::Simulator TRsim;

// Variables for tracking events
char currEvent = '\0';
char prevEvent = '\0';
// Variable for tracking number of full telemetry packets received
int numPackets = 0;

char* data;

char outputString[120];

bool activateFluidSensor = false;

void setup()
{
  TRsim.init();
  
  // Initialize the SD card, keep trying until it succeeds
  while (!setupSDCard()) {}
  debugLog("SD Card Initialized");
}

void loop()
{
  // Update the simulator to catch serial input
  TRsim.update();

  // If there is a new full telemetry packet, do some operations on it
  if (TRsim.isStreaming() == true) {
    if (TRsim.isNewData() == true) {
      // Got a new telemetry packet!
      numPackets += 1;

      // Grab new data - NOTE this sets isNewData to false!
      data = TRsim.getData();

      // If a new event has fired, identify it and print it out
      currEvent = TRsim.getEvents();
      if (currEvent != prevEvent) {
        // Find event in event structure
        for (int i=0; i<TRSim_Blue::NUMBER_EVENTS; i++) {
          if (currEvent == events[i].value) {
            debugLog("NEW EVENT: " + String(events[i].description));
            break;
          } 
        }

        handleNewEvent(currEvent);

        prevEvent = currEvent;
      }
      
      // Print every 100th packet to verify data
      if ((numPackets % 100) == 1) {
        debugLog(data);
      }
      writeTelemetryData(data);
    }
  }

  if (activateFluidSensor) {
    int fluidLevel = readFluidSensor();
    writeSensorData(TRsim.getTime(), fluidLevel, fluidLevel * 10);
  }
  else {
    // The fluid sensor will cause enough delay if activated
    delay(10);
  }
}

/**
 * @brief Handles new events from the rockets telemetry.
 * 
 * Takes an event input and uses it to trigger certain stages such
 * as activating the pump or fluid sensor while in flight.
 */
void handleNewEvent(char event)
{
  switch (event) {
    case 'B':
      // Escape Command, about to takeoff, activate camera
      break;
    case 'C':
      // Liftoff, record for a bit and then turn off camera so it can cool down
      break;
    case 'D':
      // Start recording experiment
    case 'F':
      // Coast Starting, Activate Pump and Expulsion System
      turnOnPump();
      break;
    case 'H':
      // Coast Ending, Deactivate Pump
      turnOffPump();
      break;
    case 'J':
      // Main shoots deployed, Activate water sensor and start writing data
      activateFluidSensor = true;
      break;
    case 'K':
      // Touchdown, Write to file and continue to record water sensor data
      break;
    case 'M':
      // Mission ended, deactivate all systems and perform safe shutdown
      activateFluidSensor = false;
  }
}