// // Rocket Telemetry Global Vars
// String inputString = "";
// String inputData = "";
// char oldFlightStage;
// char flightStage;
// float telemetryData[8];
// bool dataInputComplete = false;
// int telemetryIndex = 0;

// void setup()
// {
//   // Initialize serial communications at 57600 baud, as anything less is too
//   // slow for the computer to handle.
//   Serial.begin(57600);

//   // Reserve 128 bytes for the inputString (roughly 128 characters):
//   inputString.reserve(128);
// }

// void loop()
// {
//   handleTelemetryData();
// }

// /*
//   SerialEvent occurs whenever a new data comes in the hardware serial RX. This
//   routine is run between each time loop() runs, so using delay inside loop can
//   delay response. Multiple bytes of data may be available.

//   Largely the method parses the serial data and makes it more readable for other functions
// */
// void serialEvent()
// {
//   while (Serial.available())
//   {
//     // get the new byte:
//     char inChar = (char)Serial.read();

//     // !!!WARNING!!! THIS IS MOST LIKELY VERY INNEFICIENT AND COULD CAUSE PROBLEMS LATER
//     // TODO: REVISE LATER
//     inputString += inChar;

//     switch (inChar)
//     {
//     case '\n':
//       dataInputComplete = true;
//       telemetryIndex = 0;
//       break;
//     case ',':
//       if (!isAlpha(inChar)) // Check if the input is a character
//       {
//         telemetryData[telemetryIndex] = inputData.toFloat();
//         telemetryIndex++;
//       }
//       else // If the input is a character that means its a flight stage
//       {
//         flightStage = inputData[0];
//       }
//       inputData = "";
//       break;
//     default:
//       inputData += inChar;
//     }
//   }
// }

// /**
//  * @brief Handles the telemetry data.
//  * 
//  * Takes the telemetry input and uses it to trigger certain events such
//  * as activating the pump, fluid sensor, and SD card.
//  */
// void handleTelemetryData()
// {
//   if (dataInputComplete)
//   {
//     Serial.println(inputString);
//     for(int i = 0; i < 8; i++)
//     {
//       Serial.print(telemetryData[i]);
//       Serial.print(",");
//     }
//     Serial.println();
//     inputString = "";
//     dataInputComplete = false;

//     // Call helper functions such as write to SD card
//   }

//   if (oldFlightStage != flightStage)
//   {
//     Serial.print("NEW Flight Stage Detected: ");
//     Serial.println(flightStage);
//     oldFlightStage = flightStage;

//     switch (flightStage)
//     {
//       case 'F':
//         // Coast Starting, Activate Pump and Expulsion System
//         Serial.println("Coast Starting");
//         break;
//       case 'H':
//         // Coast Ending, Deactivate Pump
//         break;
//       case 'J':
//         // Main shoots deployed, Activate water sensor and start writing data
//         break;
//       case 'K':
//         // Touchdown, Write to file and continue to record water sensor data
//         break;
//     }
//   }
// }

// Last updated by: Mark DeLoura
// UPDATED: 1/12/2022
// TODO: BUG FIXING

#include <TRSim_Blue.h>

void setup(){}
void loop(){}
// /* Blue Launch demo
//  *   This simple demo reads data coming from the Future Engineers TechRise web-based simulator.
//  *   It is designed to run on a Metro M4 Express and uses the on-board Neopixel.
//  *   The demo runs a simple update loop, and does three actions:
//  *     1 - Keeps track of the number of telemetry packets received
//  *     2 - Monitors for new events and prints a message each time one occurs
//  *     3 - Prints out every 1000th telemetry packet
//  */

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

// // Set up Simulator
TRSim_Blue::Simulator TRsim;

// // Variables for tracking events
// char currEvent = '\0';
// char prevEvent = '\0';
// // Variable for tracking number of full telemetry packets received
// int numPackets = 0;

// char* data;

// char outputString[120];

// void serialPrintPacket();

// // setup()
// //   Initialization functions
// //
// void setup() {
//   // Serial = USB
//   // FESim = Serial1 = UART
//   Serial.begin(115200);
//   TRsim.init(); 

//   Serial.println("Running Blue Launch demo");
// }

// // loop()
// //   Do forever
// //
// void loop() {
//   // Update the simulator to catch serial input
//   TRsim.update();

//   // If there is a new full telemetry packet, do some operations on it
//   if (TRsim.isStreaming() == true) {
//     if (TRsim.isNewData() == true) {
//       // Got a new telemetry packet!
//       numPackets += 1;

//       // Grab new data - NOTE this sets isNewData to false!
//       data = TRsim.getData();

//       // If a new event has fired, identify it and print it out
//       currEvent = TRsim.getEvents();
//       if (currEvent != prevEvent) {
//         // Find event in event structure
//         for (int i=0; i<TRSim_Blue::NUMBER_EVENTS; i++) {
//           if (currEvent == events[i].value) {
//             Serial.print("Event: ");
//             Serial.println(events[i].description);
//             break;
//           } 
//         }
//         prevEvent = currEvent;
//       }
      
//       // Print every 1000th packet to verify data
//       if ((numPackets % 1000) == 1) {
//         serialPrintPacket();
//       }
//     }
//   }

//   delay(10);
  
// }


// void serialPrintPacket() {
//   Serial.println(data);

//   Serial.print("  events ");
//   Serial.println(TRsim.getEvents());
//   Serial.print("  time ");
//   Serial.println(TRsim.getTime());
//   Serial.print("  altitude ");
//   Serial.println(TRsim.getAltitude());
//   Serial.print("  gps altitude ");
//   Serial.println(TRsim.getGpsAltitude());
//   Serial.print("  velocity up ");
//   Serial.println(TRsim.getVelocityUp());
//   Serial.print("  velocity east ");
//   Serial.println(TRsim.getVelocityEast());
//   Serial.print("  velocity north ");
//   Serial.println(TRsim.getVelocityNorth());
//   Serial.print("  acceleration magnitude "); 
//   Serial.println(TRsim.getAccelerationMagnitude());
//   Serial.print("  acceleration x ");
//   Serial.println(TRsim.getAccelerationX());
//   Serial.print("  acceleration y ");
//   Serial.println(TRsim.getAccelerationY());
//   Serial.print("  acceleration z ");
//   Serial.println(TRsim.getAccelerationZ());
//   Serial.print("  attitude phi ");
//   Serial.println(TRsim.getAttitudePhi());
//   Serial.print("  attitude theta ");
//   Serial.println(TRsim.getAttitudeTheta());
//   Serial.print("  attitude psi ");
//   Serial.println(TRsim.getAttitudePsi());
//   Serial.print("  angular velocity x ");
//   Serial.println(TRsim.getAngularVelocityX());
//   Serial.print("  angular velocity y ");
//   Serial.println(TRsim.getAngularVelocityY());
//   Serial.print("  angular velocity z ");
//   Serial.println(TRsim.getAngularVelocityZ());
//   Serial.print("  liftoff warning ");
//   Serial.println(TRsim.getLiftoffWarning()?"true":"false");
//   Serial.print("  drogue chute warning ");
//   Serial.println(TRsim.getDrogueChuteWarning()?"true":"false");
//   Serial.print("  landing warning ");
//   Serial.println(TRsim.getLandingWarning()?"true":"false");
//   Serial.print("  chute fault warning ");
//   Serial.println(TRsim.getChuteFaultWarning()?"true":"false");
// }

