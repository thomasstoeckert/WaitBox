#include <ArduinoJson.h>

#include "AttractionWaitTime.h"

class ParkWaitTime
{
    public:
        // Constructors
        ParkWaitTime(JsonObject jsonData);
        ParkWaitTime(const char* inEntityID, AttractionWaitTime* inAttractions);

        // Getters
        String getEntityID();
        int getNumAttractions();
        AttractionWaitTime* getAttractionWaitTimes();
        AttractionWaitTime  getAttractionWaitTime(int index);
    
    private:
        String entityID;
        AttractionWaitTime* attractions;
        int numAttractions;
};