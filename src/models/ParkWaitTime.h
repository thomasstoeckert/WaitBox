#pragma once

#include <ArduinoJson.h>

#include "AttractionWaitTime.h"
#include "ConfigurationSettings.h"

#define TYPE_ATTRACTION "ATTRACTION"
#define TYPE_SHOW       "SHOW"

class ParkWaitTime
{
    public:
        // Constructors
        ParkWaitTime();
        ParkWaitTime(JsonObject jsonData, ConfigurationSettings configSettings = ConfigurationSettings());
        ParkWaitTime(const char* inEntityID, std::vector<AttractionWaitTime> inAttractions);

        // Getters
        String getEntityID();
        int getNumAttractions();
        std::vector<AttractionWaitTime> getAttractionWaitTimes();
        AttractionWaitTime  getAttractionWaitTime(int index);
    
    private:
        String entityID;
        std::vector<AttractionWaitTime> attractions;
        int numAttractions;
};