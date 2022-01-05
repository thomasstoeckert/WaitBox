#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

class ConfigurationSettings
{
    public:
        ConfigurationSettings();
        ConfigurationSettings(JsonObject configurationData);

        int getRefreshFrequency();

        int getNumParks();
        String getSelectedParkID(int parkIndex);
        
        std::vector<String> getAttractionFilterForPark(int parkIndex);
    private:
        int refreshFrequency;

        std::vector<String> parkFilters;
        std::vector<std::vector<String>> attractionFilters;
};