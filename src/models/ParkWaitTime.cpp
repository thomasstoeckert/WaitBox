#include "ParkWaitTime.h"

ParkWaitTime::ParkWaitTime()
{
    // Assign some dummy values
    name = String("Dummy Park");
    attractions = std::vector<AttractionWaitTime>();
}

ParkWaitTime::ParkWaitTime(const char *inName, std::vector<AttractionWaitTime> inAttractions)
{
    // Copy the park ID over
    name = String(inName);

    // Copy the attractions list over
    attractions = inAttractions;
}

ParkWaitTime::ParkWaitTime(JsonObject jsonData, ConfigurationSettings configSettings, int parkIndex)
{
    // Copy our park ID over
    name = String(jsonData["name"].as<const char *>());

    // Get our list of attractions
    JsonArray attractionData = jsonData["liveData"].as<JsonArray>();

    // Get the length of the list
    int lenAttractionData = attractionData.size();
    int attractionCount = 0;

    // Allocate space in our array - we won't use it all, but that's okay for now.
    attractions = std::vector<AttractionWaitTime>();

    std::vector<String> attractionFilters = configSettings.getAttractionFilterForPark(parkIndex);

    // Loop through each attraction, parsing it, and storing it
    for (int i = 0; i < lenAttractionData; i++)
    {
        // Parse the data
        JsonObject singleAttractionData = attractionData[i].as<JsonObject>();
        AttractionWaitTime parsedAttraction = AttractionWaitTime(singleAttractionData);

        // Filter out things that are not attractions
        if (parsedAttraction.getType() != "ATTRACTION") continue;

        // Check against this attraction's ID
        if (attractionFilters.size() > 0)
        {
            bool isInFilter = false;
            // For all IDs in filter,
            for (int j = 0; j < attractionFilters.size(); j++)
            {
                // If our ID is found, mark as found and break
                if (parsedAttraction.getEntityID() == attractionFilters[j])
                {
                    isInFilter = true;
                    break;
                }
            }

            if (!isInFilter)
            {
                continue;
            };
        }

        // If we've made it here, the attraction is okay to use. Store it.
        attractionCount++;
        attractions.push_back(parsedAttraction);
    }

    numAttractions = attractionCount;
}

String ParkWaitTime::getName()
{
    return name;
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