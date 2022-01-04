#include <Arduino.h>
#include <WiFiManager.h>

// Project imports
#include "managers/ConfigurationManager.h"
#include "managers/WaitTimesManager.h"
#include "managers/DisplayManager.h"

#include "models/ConfigurationSettings.h"

#define SLEEP_MINUTES(minutes) (minutes * 60 * 1000)

ConfigurationManager configurationManager;
DisplayManager       displayManager;
WiFiManager          wifiManager;
WaitTimesManager     waitTimesManager;

void setup() 
{
    // Begin our serial communication
    Serial.begin(115200);
    while(!Serial) { delay(10); }
    Serial.println("");
    Serial.println("WaitTimes Box Project - Beginning Setup");
    Serial.println("");

    // Load Settings
    configurationManager.loadSettings();

    // Configure Display
    displayManager.setup();

    // Start the WiFi Manager
    wifiManager.autoConnect("Wait Times Box", "waittimes"); // TODO: make proper password

    // Fetch initial data for the Wait Times Manager
    waitTimesManager.init();
}

void loop()
{
    const char* timeString = String(millis() / 60000).c_str();
    // Every 180s (three minutes)...
    Serial.printf("\n[%s] Waking up from sleep\n", timeString);

    ConfigurationSettings latestSettings = configurationManager.getCurrentSettings();

    // Fetch the latest wait times information from the server
    Serial.printf("[%s] Fetching updates information from the server\n", timeString);
    waitTimesManager.updateData(latestSettings);

    std::array<ParkWaitTime, 4> latestWaits = waitTimesManager.getWaitTimes();

    // Update the display
    Serial.printf("[%s] Refreshing display with latest information\n", timeString);
    //displayManager.drawDummyScreen();
    displayManager.drawWaits(latestWaits);

    // Go back to sleep for three minutes
    Serial.printf("[%s] Fixed update complete. Going back to sleep.\n", timeString);
    delay(SLEEP_MINUTES(5));
}