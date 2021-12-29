#pragma once

#include <ArduinoJson.h>

class AttractionWaitTime
{
    public:
        // Constructors
        AttractionWaitTime(const char* inEntityID, const char* inName, const char* inStatus, const char* inType, int inWait);
        AttractionWaitTime(JsonObject jsonData);
        
        // Getters
        String getEntityID();
        String getName();
        String getStatus();
        String getType();
        int   getWait();

    private:
        String entityID;
        String name;
        String status;
        String type;
        int wait;
};