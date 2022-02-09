#include <TRSim_Blue.h>

// Variables for tracking events
char currEvent = '\0';
char prevEvent = '\0';
// Variable for tracking number of full telemetry packets received
int numPackets = 0;

char* data;

char outputString[120];

void serialPrintPacket();

// Activation Vars
bool activateFluidSensor = false;
int lastUpdateTime = 0;

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

void setup()
{
  Serial.begin(115200);
  TRsim.init(); 

  Serial.println("Running Blue Launch demo");

  // Initialize the SD card, keep trying until it succeeds
  while (!setupSDCard()) {}
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
      handleEvent();
      
      // Print every 1000th packet to verify data
      if ((numPackets % 1000) == 1) {
        serialPrintPacket();
        
      }
    }
  }

  delay(10);

  // switch (flightStage)
  // {
  //   case 'F':
  //     // Coast Starting, Activate Pump and Expulsion System
  //     turnOnPump();
  //     Serial.println("Coast Starting");
  //     break;
  //   case 'H':
  //     // Coast Ending, Deactivate Pump
  //     turnOffPump();
  //     break;
  //   case 'J':
  //     // Main shoots deployed, Activate water sensor and start writing data
  //     activateFluidSensor = true;
  //     break;
  //   case 'K':
  //     // Touchdown, Write to file and continue to record water sensor data
  //     break;
  //   case 'M':
  //     // Mission ended, deactivate all systems and perform safe shutdown
  //     activateFluidSensor = false;
  // }

  // if (activateFluidSensor) {
  //   int fluidLevel = readFluidSensor();
  //   writeSensorData(telemetryData[0], fluidLevel, fluidLevel * 10);
  // }
}

/**
 * @brief Handles the event data.
 * 
 * Takes the telemetry input and uses it to trigger certain events such
 * as activating the pump, fluid sensor, and SD card.
 */
void handleEvent()
{
  if (currEvent != prevEvent) {
    // Find event in event structure
    for (int i=0; i<TRSim_Blue::NUMBER_EVENTS; i++) {
      if (currEvent == events[i].value) {
        Serial.print("Event: ");
        Serial.println(events[i].description);
        break;
      } 
    }
    prevEvent = currEvent;
  }
}

void serialPrintPacket() {
  Serial.println(data);

  Serial.print("  events ");
  Serial.println(TRsim.getEvents());
  Serial.print("  time ");
  Serial.println(TRsim.getTime());
  Serial.print("  altitude ");
  Serial.println(TRsim.getAltitude());
  Serial.print("  gps altitude ");
  Serial.println(TRsim.getGpsAltitude());
  Serial.print("  velocity up ");
  Serial.println(TRsim.getVelocityUp());
  Serial.print("  velocity east ");
  Serial.println(TRsim.getVelocityEast());
  Serial.print("  velocity north ");
  Serial.println(TRsim.getVelocityNorth());
  Serial.print("  acceleration magnitude "); 
  Serial.println(TRsim.getAccelerationMagnitude());
  Serial.print("  acceleration x ");
  Serial.println(TRsim.getAccelerationX());
  Serial.print("  acceleration y ");
  Serial.println(TRsim.getAccelerationY());
  Serial.print("  acceleration z ");
  Serial.println(TRsim.getAccelerationZ());
  Serial.print("  attitude phi ");
  Serial.println(TRsim.getAttitudePhi());
  Serial.print("  attitude theta ");
  Serial.println(TRsim.getAttitudeTheta());
  Serial.print("  attitude psi ");
  Serial.println(TRsim.getAttitudePsi());
  Serial.print("  angular velocity x ");
  Serial.println(TRsim.getAngularVelocityX());
  Serial.print("  angular velocity y ");
  Serial.println(TRsim.getAngularVelocityY());
  Serial.print("  angular velocity z ");
  Serial.println(TRsim.getAngularVelocityZ());
  Serial.print("  liftoff warning ");
  Serial.println(TRsim.getLiftoffWarning()?"true":"false");
  Serial.print("  drogue chute warning ");
  Serial.println(TRsim.getDrogueChuteWarning()?"true":"false");
  Serial.print("  landing warning ");
  Serial.println(TRsim.getLandingWarning()?"true":"false");
  Serial.print("  chute fault warning ");
  Serial.println(TRsim.getChuteFaultWarning()?"true":"false");
}
