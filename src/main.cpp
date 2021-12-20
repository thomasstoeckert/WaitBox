#include <Arduino.h>
#include <WiFiManager.h>

// Project imports
#include "managers/ConfigurationManager.h"
#include "managers/WaitTimesManager.h"
#include "managers/DisplayManager.h"

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
    // Every 180s (three minutes)...
    Serial.println("\nWaking Up - Beginning fixed update");

    // Fetch the latest wait times information from the server
    Serial.println("Fetching updates information from the server");
    waitTimesManager.updateData();

    // Update the display
    Serial.println("Drawing a dummy screen");
    displayManager.drawDummyScreen();

    // Go back to sleep for three minutes
    Serial.println("Fixed update complete. Going back to sleep.");
    delay(SLEEP_MINUTES(5));
}