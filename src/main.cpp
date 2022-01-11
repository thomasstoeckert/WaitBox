#include <Arduino.h>
#include <WiFiManager.h>
#include <TaskScheduler.h>

// Project imports
#include "managers/ConfigurationManager.h"
#include "managers/WaitTimesManager.h"
#include "managers/DisplayManager.h"

#include "models/ConfigurationSettings.h"

#define SLEEP_MINUTES(minutes) (minutes * 60 * 1000)
#define PIN_RESET_BUTTON 14

ConfigurationManager configurationManager;
DisplayManager       displayManager;
WiFiManager          wifiManager;
WaitTimesManager     waitTimesManager;

// Wifi Configuration Parameters
WiFiManagerParameter configParameter("config", "Paste Configuration Below:", configurationManager.configurationString, 2048);

// WiFi Manager Callbacks
void configModeCallback(WiFiManager *localWiFiManager);
void configSaveSettingsCallback();

// Task Scheduler Definitions
Scheduler runner;

// Task Definitions (with defaults)
void updateCallback();
void resetConfigurationCallback();
Task updateTask(SLEEP_MINUTES(5), -1, updateCallback);
Task resetConfiguration(TASK_IMMEDIATE, -1, resetConfigurationCallback);


void IRAM_ATTR resetButtonISR()
{
    Serial.println("Hey - ISR");
    resetConfiguration.restart();
    resetConfiguration.enable();
}

void setup() 
{
    // Begin our serial communication
    Serial.begin(115200);
    while(!Serial) { delay(10); }
    Serial.println("");
    Serial.println("WaitTimes Box Project - Beginning Setup");
    Serial.println("");

    // Establish our interrupt
    pinMode(PIN_RESET_BUTTON, INPUT);
    attachInterrupt(digitalPinToInterrupt(PIN_RESET_BUTTON), resetButtonISR, FALLING);

    // Load Settings
    configurationManager.loadSettings();

    // Configure Display
    displayManager.setup();

    // Config and establish the wifi manager
    wifiManager.addParameter(&configParameter);
    wifiManager.setSaveConfigCallback(configSaveSettingsCallback);
    wifiManager.setAPCallback(configModeCallback);

    // Just for testing
    wifiManager.autoConnect("Wait Times Box", "waittimes"); // TODO: make proper password

    // Configure our task
    ConfigurationSettings settings = configurationManager.getCurrentSettings();
    updateTask.setInterval(SLEEP_MINUTES(settings.getRefreshFrequency()));

    // Fetch initial data for the Wait Times Manager
    waitTimesManager.init();

    // Establish our runner
    runner.init();

    // Add our reset task

    // Add and run our primary task
    runner.addTask(updateTask);
    runner.addTask(resetConfiguration);
    updateTask.enable();
}

void loop()
{
    runner.execute();
}

void updateCallback()
{
    unsigned long minuteTimestamp = millis() / 60000;
    
    Serial.printf("\n[%lu] Waking up from sleep\n", minuteTimestamp);

    ConfigurationSettings latestSettings = configurationManager.getCurrentSettings();

    // Fetch the latest wait times information from the server
    Serial.printf("[%lu] Fetching updates information from the server\n", minuteTimestamp);
    waitTimesManager.updateData(latestSettings);

    std::vector<ParkWaitTime> latestWaits = waitTimesManager.getWaitTimes();

    // Update the display
    Serial.printf("[%lu] Refreshing display with latest information\n", minuteTimestamp);
    //displayManager.drawDummyScreen();
    displayManager.drawWaits(latestWaits);

    // Go back to sleep for three minutes
    Serial.printf("[%lu] Fixed update complete. Going back to sleep.\n", minuteTimestamp);
}

void configModeCallback(WiFiManager *localWiFiManager)
{
    // Our system is in configuration mode. Go through and print out
    // the configuration IP into serial, and also prepare our display
    Serial.println("[WiFiManager] Entering Configuration Mode");
    //Serial.println("")
    
}

void configSaveSettingsCallback() 
{
    // Tell our configuration manager to save the configuration data
    configurationManager.saveSettings(String(configParameter.getValue()));

    // Enable our primary task (if it isn't already)
    updateTask.enableIfNot();
}

unsigned long lastRunCallback = 0;
void resetConfigurationCallback()
{
    Serial.println("Hey uh so it started");

    // Do our software debouncing
    unsigned long now = millis();
    if(now - lastRunCallback <= 250) return;
    lastRunCallback = now;

    Serial.println("Hey - Reset Configuration Callback");

    // Tell the wifi manager to reset its settings
    wifiManager.resetSettings();
    
    // Restart the device I guess
    ESP.restart();
}
