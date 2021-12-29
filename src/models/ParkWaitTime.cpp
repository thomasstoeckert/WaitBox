#include "ParkWaitTime.h"

ParkWaitTime::ParkWaitTime()
{
    // Assign some dummy values
    entityID = String("Dummy Park");
    attractions = std::vector<AttractionWaitTime>();
}

ParkWaitTime::ParkWaitTime(const char *inEntityID, std::vector<AttractionWaitTime> inAttractions)
{
    // Copy the park ID over
    entityID = String(inEntityID);

    // Copy the attractions list over
    attractions = inAttractions;
}

ParkWaitTime::ParkWaitTime(JsonObject jsonData, ConfigurationSettings configSettings)
{
    // Copy our park ID over
    entityID = String(jsonData["id"].as<const char *>());

    // Get our list of attractions
    JsonArray attractionData = jsonData["liveData"].as<JsonArray>();

    // Get the length of the list
    int lenAttractionData = attractionData.size();
    int attractionCount = 0;

    // Allocate space in our array - we won't use it all, but that's okay for now.
    attractions = std::vector<AttractionWaitTime>();

    // Loop through each attraction, parsing it, and storing it
    for (int i = 0; i < lenAttractionData; i++)
    {

        // Parse the data
        JsonObject singleAttractionData = attractionData[i].as<JsonObject>();
        AttractionWaitTime parsedAttraction = AttractionWaitTime(singleAttractionData);

        // Our parse settings

        String parsedAttractionType = parsedAttraction.getType();

        // If we're an attraction, and attractions are disabled, skip
        if (parsedAttractionType == TYPE_ATTRACTION &&
            !configSettings.getShowAttractions())
        {
            Serial.println("Attractions Disabled");
            continue;
        };

        // If we're a show, and shows are disabled, skip
        if (parsedAttractionType == TYPE_SHOW &&
            !configSettings.getShowShows())
        {
            Serial.println("Shows Disabled");
            continue;
        };

        // If we're neither a show or attraction, and others are disabled, skip
        if (parsedAttractionType != TYPE_ATTRACTION &&
            parsedAttractionType != TYPE_SHOW && !configSettings.getShowOthers())
        {
            Serial.println("Others Disabled");
            continue;
        };
        ;

        // Check against this attraction's ID
        if (configSettings.getNumFilters() > 0)
        {
            bool isInFilter = false;
            // For all IDs in filter,
            for (int j = 0; j < configSettings.getNumFilters(); j++)
            {
                // If our ID is found, mark as found and break
                if (parsedAttraction.getEntityID() == configSettings.getFilter(j))
                {
                    isInFilter = true;
                    break;
                }
            }

            if (!isInFilter)
            {
                Serial.println("Not in filter");
                continue;
            };
        }

        // If we've made it here, the attraction is okay to use. Store it.
        attractionCount++;
        attractions.push_back(parsedAttraction);
    }

    numAttractions = attractionCount;
}

String ParkWaitTime::getEntityID()
{
    return entityID;
}

int ParkWaitTime::getNumAttractions()
{
    return numAttractions;
}

std::vector<AttractionWaitTime> ParkWaitTime::getAttractionWaitTimes()
{
    return attractions;
}

AttractionWaitTime ParkWaitTime::getAttractionWaitTime(int index)
{
    return attractions[index];
}