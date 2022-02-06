// Rocket Telemetry Global Vars
String inputString = "";
String inputData = "";

// Flight Stage Vars
char flightStage;

// Telemetry Data Vars
float telemetryData[8];
int telemetryIndex = 0;
bool dataInputComplete = false;

// Activation Vars
bool activateFluidSensor = false;
int lastUpdateTime = 0;

void setup()
{
  // Reserve 128 bytes for the inputString (roughly 128 characters):
  inputString.reserve(128);

  // Initialize the SD card, keep trying until it succeeds
  while (!setupSDCard()) {}
}

void loop()
{
  handleTelemetryData();
  
  Serial.print("NEW Flight Stage Detected: ");
  Serial.println(flightStage);

  switch (flightStage)
  {
    case 'F':
      // Coast Starting, Activate Pump and Expulsion System
      turnOnPump();
      Serial.println("Coast Starting");
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

  if (activateFluidSensor) {
    int fluidLevel = readFluidSensor();
    writeSensorData(telemetryData[0], fluidLevel, fluidLevel * 10);
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.

  Largely the method parses the serial data and makes it more readable for other functions
*/
void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();

    // !!!WARNING!!! THIS IS MOST LIKELY VERY INNEFICIENT AND COULD CAUSE PROBLEMS LATER
    // TODO: REVISE LATER
    inputString += inChar;

    switch (inChar)
    {
    case '\n':
      dataInputComplete = true;
      telemetryIndex = 0;
      break;
    case ',':
      if (!isAlpha(inChar)) // Check if the input is a character
      {
        telemetryData[telemetryIndex] = inputData.toFloat();
        telemetryIndex++;
      }
      else // If the input is a character that means its a flight stage
      {
        flightStage = inputData[0];
      }
      inputData = "";
      break;
    default:
      inputData += inChar;
    }
  }
}

/**
 * @brief Handles the telemetry data.
 * 
 * Takes the telemetry input and uses it to trigger certain events such
 * as activating the pump, fluid sensor, and SD card.
 */
void handleTelemetryData()
{
  if (dataInputComplete)
  {
    writeTelemetryData(inputString);

    inputString = "";
    dataInputComplete = false;
  }
}
