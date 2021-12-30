#include "WaitTimesManager.h"

WaitTimesManager::WaitTimesManager() :
    webResponseBuffer(32000), parkWaitTimes{ParkWaitTime(), ParkWaitTime(), ParkWaitTime(), ParkWaitTime()}
{
    // Prepare our JSON filter

    // Keep park entity IDs in park live data responses
    deserializeJson(attractionResultFilter, FILTER_STRING, DeserializationOption::NestingLimit(15));
}

void WaitTimesManager::init()
{
    // Fetch all parks list from server (Eventually)
    //serializeJsonPretty(attractionResultFilter, Serial);
}

bool WaitTimesManager::updateData(ConfigurationSettings configSettings)
{
    // Fetch data from our selected parks/attractions, feeding them
    // into our data structures.

    // For each park...
    int numParks = configSettings.getNumParks();
    for(int i = 0; i < numParks; i++)
    {
        // Fetch the data from the web, parsed into JSON
        fetchParkWaits(configSettings.getSelectedParkID(i).c_str());

        ////// Move that into our data structures //////
        
        // Parse it into a park
        ParkWaitTime parsedPark = ParkWaitTime(webResponseBuffer.as<JsonObject>(), configSettings, i);

        // Print out our response
        Serial.println("Wait Times Object Result: ");
        Serial.printf("\tParkName: %s\n", parsedPark.getName().c_str());
        Serial.printf("\tNumAttractions: %d\n", parsedPark.getNumAttractions());

        // Store this park object
        parkWaitTimes[i] = parsedPark;
    }

    
    return true;
}

bool WaitTimesManager::fetchParkWaits(const char* parkID)
{
    // If we're not connected to WiFi, this is going to fail.
    if(WiFi.status() != WL_CONNECTED) return false;

    String builtURL = String(baseURL);
    builtURL += slugEntity + String(parkID) + slugLive;

    // Establish our client
    WiFiClientSecure client;
    HTTPClient http;

    // Configure various parts of the request
    // HTTP1.0 required for a stream output
    http.useHTTP10(true); 
    client.setCACert(root_ca);
    http.begin(client, builtURL);
    http.setRedirectLimit(32);
    http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);

    Serial.println("Sending park wait request...");

    int statusCode = http.sendRequest("GET");

    Serial.printf("Got our response code of %d\n", statusCode);
    Serial.println("Request sent. Parsing...");

    DeserializationError error = deserializeJson(webResponseBuffer, 
        http.getStream(), DeserializationOption::Filter(attractionResultFilter), DeserializationOption::NestingLimit(10));

    Serial.println("Parse complete.");

    if(error)
    {
        Serial.print("DeserializedJSON Failed: ");
        Serial.println(error.c_str());
        http.end();
        return false;
    }

    // Disconnect
    http.end();

    return true;
}

std::array<ParkWaitTime, 4> WaitTimesManager::getWaitTimes()
{
    return parkWaitTimes;
}