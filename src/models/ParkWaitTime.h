#pragma once

#include <ArduinoJson.h>
#include <array>

#include "AttractionWaitTime.h"
#include "ConfigurationSettings.h"

#define TYPE_ATTRACTION "ATTRACTION"
#define TYPE_SHOW       "SHOW"

class ParkWaitTime
{
    public:
        // Constructors
        ParkWaitTime();
        ParkWaitTime(JsonObject jsonData, ConfigurationSettings configSettings = ConfigurationSettings(), int parkIndex = 0);
        ParkWaitTime(const char* inEntityID, std::vector<AttractionWaitTime> inAttractions);

        // Getters
        String getName();
        int getNumAttractions();
        std::vector<AttractionWaitTime> getAttractionWaitTimes();
        AttractionWaitTime  getAttractionWaitTime(int index);
    
    private:
        String name;
        std::vector<AttractionWaitTime> attractions;
        int numAttractions;
};