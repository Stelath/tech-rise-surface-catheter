#include <SPI.h>
#include <SD.h>

// SD Card Pins
const byte SD_PIN = 4;

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
        return false;
    }
}

/**
 * @brief Writes an event to the necessary files.
 * 
 * Stores sensor data from the experiment in a CSV file for later
 * review and analysis.
 * 
 * @param timestamp The time in milliseconds from rocket launch.
 * @param fluidLevel The level output of the fluid sensor.
 * @param volume The volume of fluid in the reservoir calculated
 *               with the fluid level (in milliliters).
 */
void writeEvent(long timestamp, String event)
{
    File eventDataFile = SD.open("edata.csv", FILE_WRITE);
    if (eventDataFile) // Make sure the file opened properly
    {
        eventDataFile.println(String(timestamp) + "," + event);
    }
    eventDataFile.close();

    File sensorDataFile = SD.open("sdata.csv", FILE_WRITE);
    if (sensorDataFile) // Make sure the file opened properly
    {
        sensorDataFile.println(String(timestamp) + "," + event);
    }
    sensorDataFile.close();
}

/**
 * @brief Writes given data to the file in a CSV format.
 * 
 * Stores sensor data from the experiment in a CSV file for later
 * review and analysis.
 * 
 * @param timestamp The time in milliseconds from rocket launch.
 * @param fluidLevel The level output of the fluid sensor.
 * @param volume The volume of fluid in the reservoir calculated
 *               with the fluid level (in milliliters).
 */
void writeSensorData(long timestamp, int fluidLevel)
{
    File sensorDataFile = SD.open("sdata.csv", FILE_WRITE);
    if (sensorDataFile) // Make sure the file opened properly
    {
        sensorDataFile.println(String(timestamp) + "," + String(fluidLevel));
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
