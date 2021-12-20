#include "ParkWaitTime.h"

ParkWaitTime::ParkWaitTime(const char* inEntityID, AttractionWaitTime* inAttractions)
{
    // Copy the park ID over
    entityID = String(inEntityID);

    // Copy the attractions list over
    attractions = inAttractions;
}

ParkWaitTime::ParkWaitTime(JsonObject jsonData)
{
    // Copy our park ID over
    entityID = String(jsonData["id"].as<const char*>());

    // Get our list of attractions
    JsonArray attractionData = jsonData["liveData"].as<JsonArray>();

    // Get the length of the list
    int lenAttractionData = attractionData.size();

    // Allocate space in our array
    attractions = (AttractionWaitTime*) calloc(lenAttractionData, sizeof(AttractionWaitTime));

    // Loop through each attraction, parsing it, and storing it
    for(int i = 0; i < lenAttractionData; i++) {

        // Parse the data
        JsonObject singleAttractionData = attractionData[i].as<JsonObject>();
        AttractionWaitTime parsedAttraction = AttractionWaitTime(singleAttractionData);

        // Store it into our newly-created attractions list
        attractions[i] = parsedAttraction;
    }
}

String ParkWaitTime::getEntityID()
{
    return entityID;
}

int ParkWaitTime::getNumAttractions()
{
    return numAttractions;
}

AttractionWaitTime* ParkWaitTime::getAttractionWaitTimes()
{
    return attractions;
}

AttractionWaitTime ParkWaitTime::getAttractionWaitTime(int index) 
{
    return attractions[index];
}