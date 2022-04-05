// Sensor pins
const int fluidSensorPower = 5;
const int fluidSensorPin = A1;

void setup() {
	// Set D7 as an OUTPUT
	pinMode(fluidSensorPower, OUTPUT);
	
	// Set to LOW so no power flows through the sensor
	digitalWrite(fluidSensorPower, LOW);
	
	Serial.begin(115200);
}

void loop() {
	//get the reading from the function below and print it
	int level = readSensor();
	
	Serial.print("Water level: ");
	Serial.println(level);
	
	delay(1000);
}

/**
 * @brief Returns the reading of the Water Level Sensor.
 * 
 * Gets the level of water in the pump reservoir and returns
 * the value.
 * 
 * @return int Returns the level of the water in the reservoir.
 */
int readSensor() {
	digitalWrite(fluidSensorPower, HIGH);			// Turn the sensor ON
	delay(10);										// wait 10 milliseconds
	int waterLevel = analogRead(fluidSensorPin);	// Read the analog value form sensor
	digitalWrite(fluidSensorPower, LOW);			// Turn the sensor OFF

	return waterLevel;								// Return reading
}