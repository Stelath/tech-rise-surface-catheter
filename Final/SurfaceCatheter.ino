#include <TRSim_Blue.h>

// Set up events
typedef struct _eventDetails
{
  char value;
  const char *description;
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
    {TRSim_Blue::EVENT_MISSION_END, "Mission End", 0x333333}};

// Set up Simulator
TRSim_Blue::Simulator TRsim;

// Variables for tracking events

char currEvent = '\0';
char prevEvent = '\0';
// Variable for tracking number of full telemetry packets received
int numPackets = 0;

char *data;

char outputString[120];

bool activateFluidSensor = false;

void setup()
{
  delay(15000);
  TRsim.init();
  setupComponents();
  setupCamera();
  // Initialize the SD card, keep trying until it succeeds
  while (!setupSDCard())
  {
  }
  writeEvent(0, "SD Card Initialized");
}

void loop()
{
  // Update the simulator to catch serial input
  TRsim.update();

  // If there is a new full telemetry packet, do some operations on it
  if (TRsim.isStreaming() == true)
  {
    if (TRsim.isNewData() == true)
    {
      // Got a new telemetry packet!
      numPackets += 1;

      // Grab new data - NOTE this sets isNewData to false!
      data = TRsim.getData();

      // If a new event has fired, identify it and print it out
      currEvent = TRsim.getEvents();
      if (currEvent != prevEvent)
      {
        // Find event in event structure
        for (int i = 0; i < TRSim_Blue::NUMBER_EVENTS; i++)
        {
          if (currEvent == events[i].value)
          {
            writeEvent(TRsim.getTime(), "NEW EVENT: " + String(events[i].description));
            handleNewEvent(events[i].value);
            break;
          }
        }

        prevEvent = currEvent;
      }
      writeTelemetryData(data);
    }
  }

  if (activateFluidSensor)
  {
    int fluidLevel = readFluidSensor();
    writeSensorData(TRsim.getTime(), fluidLevel);
  }
  else
  {
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
  if (event == TRSim_Blue::EVENT_LIFTOFF)
  {
    // Liftoff
    writeEvent(TRsim.getTime(), F("Camera Activating"));
    turnOnCameraLight();
    turnOnCamera();
    writeEvent(TRsim.getTime(), F("Camera Activated"));
    activateFluidSensor = true;
    writeEvent(TRsim.getTime(), F("Activated Fluid Sensor"));
  }
  else if (event == TRSim_Blue::EVENT_MECO)
  {
    // Start recording experiment
    activateFluidSensor = false; // Getting baseline data for fluid sensor
    writeEvent(TRsim.getTime(), F("Deactivated Fluid Sensor"));
  }
  else if (event == TRSim_Blue::EVENT_COAST_START)
  {
    // Coast Starting, Activate Pump and Expulsion System
    writeEvent(TRsim.getTime(), F("Pump and Expulsion System Activating"));
    turnOnPump();
    turnOnExpulsion();
    writeEvent(TRsim.getTime(), F("Pump and Expulsion System Activated"));
  }
  else if (event == TRSim_Blue::EVENT_COAST_END)
  {
    // Coast Ending, Deactivate Pump
    writeEvent(TRsim.getTime(), F("Pump and Expulsion System Deactivating"));
    turnOffPump();
    turnOffExpulsion();
    writeEvent(TRsim.getTime(), F("Pump and Expulsion System Deactivated"));
  }
  else if (event == TRSim_Blue::EVENT_MAIN)
  {
    // Main shoots deployed, Activate water sensor and start writing data
    activateFluidSensor = true;
    writeEvent(TRsim.getTime(), F("Activated Fluid Sensor"));
  }
  else if (event == TRSim_Blue::EVENT_TOUCHDOWN)
  {
    // Touchdown, deactivate all systems and perform safe shutdown
    activateFluidSensor = false;
    writeEvent(TRsim.getTime(), F("Deactivated Fluid Sensor"));
    turnOffCameraLight();
    turnOffCamera();
    writeEvent(TRsim.getTime(), F("Deactivated Camera"));
    writeEvent(TRsim.getTime(), F("Shutting Down"));
  }
  // else if (event == TRSim_Blue::EVENT_SAFING)
  // {
  //   // Mission ended
  // }
}