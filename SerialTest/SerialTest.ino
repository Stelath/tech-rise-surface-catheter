// Rocket Telemetry Global Vars
String inputString = "";
String inputData = "";
char oldFlightStage;
char flightStage;
float telemetryData[8];
bool dataInputComplete = false;
int telemetryIndex = 0;

void setup()
{
  // Initialize serial communications at 57600 baud, as anything less is too
  // slow for the computer to handle.
  Serial.begin(57600);

  // Reserve 128 bytes for the inputString (roughly 128 characters):
  inputString.reserve(128);
}

void loop()
{
  handleTelemetryData();
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
    Serial.println(inputString);
    for(int i = 0; i < 8; i++)
    {
      Serial.print(telemetryData[i]);
      Serial.print(",");
    }
    Serial.println();
    inputString = "";
    dataInputComplete = false;

    // Call helper functions such as write to SD card
  }

  if (oldFlightStage != flightStage)
  {
    Serial.print("NEW Flight Stage Detected: ");
    Serial.println(flightStage);
    oldFlightStage = flightStage;

    switch (flightStage)
    {
      case 'F':
        // Coast Starting, Activate Pump and Expulsion System
        Serial.println("Coast Starting");
        break;
      case 'H':
        // Coast Ending, Deactivate Pump
        break;
      case 'J':
        // Main shoots deployed, Activate water sensor and start writing data
        break;
      case 'K':
        // Touchdown, Write to file and continue to record water sensor data
        break;
    }
  }
}
