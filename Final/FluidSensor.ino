// Pin Definitions:
const int FS_POWER_PIN = 7;
const int FS_READ_PIN = A0;

/**
 * @brief Initializes the fluid sensor.
 */
void setupFluidSensor() {
	// Set D7 as an OUTPUT
	pinMode(FS_POWER_PIN, OUTPUT);
	
	// Set to LOW so no power flows through the sensor
	digitalWrite(FS_POWER_PIN, LOW);
}

void loop() {
	//get the reading from the function below and print it
	int level = readFluidSensor();
	
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
int readFluidSensor() {
	digitalWrite(FS_POWER_PIN, HIGH);			// Turn the sensor ON
	delay(10);										// wait 10 milliseconds
	int waterLevel = analogRead(FS_READ_PIN);	// Read the analog value form sensor
	digitalWrite(FS_POWER_PIN, LOW);			// Turn the sensor OFF

	return waterLevel;								// Return reading
}