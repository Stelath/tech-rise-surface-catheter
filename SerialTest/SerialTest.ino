// Rocket Telemetry Global Vars
String inputString = "";
String inputData = "";
char oldFlightStage = 'A';
char flightStage;
float telemetryData[8];
bool dataInputComplete = false;
int telemetryIndex = 0;

void setup()
{
  // Initialize serial communications at 57600 baud, as anything less is too
  // slow for the computer to handle.
  Serial.begin(57600);

  // Reserve 256 bytes for the inputString:
  inputString.reserve(256);
}

void loop()
{
  handleTelemetryData();
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
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

void handleTelemetryData()
{
  if (dataInputComplete)
  {
    Serial.println(inputString);
    inputString = "";
    dataInputComplete = false;
  }
}
