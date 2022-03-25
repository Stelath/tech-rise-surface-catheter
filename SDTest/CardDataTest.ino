#include <SPI.h>
#include <SD.h>

const byte SD_PIN = 4;

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {} // Wait for serial port to connect. Needed for native USB port only
    Serial.println("Serial Initialized");

    Serial.println("Initializing SD card...");
    while (!setupSDCard()) {} // Initialize the SD card, keep trying until it succeeds
    Serial.println("initialization done.");
}

void loop()
{
    writeSensorData(millis(), 10, 30);
    writeTelemetryData("Telemetry Test Value");
    delay(50);
}

/**
 * @brief A setup method for the SD card.
 * 
 * @return true Returns true if the SD card was sucessfully initialized.
 * @return false Returns false if the SD card failed to initialize.
 */
bool setupSDCard()
{
    if (SD.begin(SD_PIN))
    {
        return true;
    }
    else
    {
        Serial.println("Failed to initialize");
        return false;
    }
}

/**
 * @brief Writes given data to the file in a CSV format.
 * 
 * Stores sensor data from the experiement in a CSV file for later
 * review and analysis.
 * 
 * @param timestamp The time in milliseconds from rocket launch.
 * @param fluidLevel The level output of the fluid sensor.
 * @param volume The volume of fluid in the reservoir calculated
 *               with the fluid level (in milliliters).
 */
void writeSensorData(long timestamp, int fluidLevel, int volume)
{
    File sensorDataFile = SD.open("sdata.csv", FILE_WRITE);
    if (sensorDataFile) // Make sure the file opened properly
    {
        sensorDataFile.println(String(timestamp) + "," + String(fluidLevel) + "," + String(volume));
    }
    sensorDataFile.close();
}

/**
 * @brief Writes given data to the file in a CSV format.
 * 
 * Stores Tech Rise rocket telemetry data from the experiement in
 * a CSV file for later review and analysis; most likely in tandem
 * with sensor data.
 * 
 * @param telemetry The Tech Rise rocket telemetry passed to the
 *                  Arduino through the serial bus.
 */
void writeTelemetryData(String telemetry)
{
    File telemetryDataFile = SD.open("tdata.csv", FILE_WRITE);
    if (telemetryDataFile) // Make sure the file opened properly
    {
        telemetryDataFile.println(telemetry);
    }
    telemetryDataFile.close();
}