#include "WaitTimesManager.h"

WaitTimesManager::WaitTimesManager() :
    webResponseBuffer(32000)
{
    // Prepare our JSON filter

    // Keep park entity IDs in park live data responses
    attractionResultFilter["id"] = true;
    
    // Keep attraction names, IDs, status, and standby queue wait times
    JsonObject attractionResultFilterLiveData = attractionResultFilter["liveData"].createNestedObject();
    attractionResultFilterLiveData["name"] = true;
    attractionResultFilterLiveData["entityType"] = true;
    attractionResultFilterLiveData["status"] = true;
    JsonObject attractionResultFilterStandby = attractionResultFilterLiveData["queue"].createNestedObject("STANDBY");
    attractionResultFilterStandby["waitTime"] = true;

}

void WaitTimesManager::init()
{
    // Fetch all parks list from server (Eventually)
    serializeJsonPretty(attractionResultFilter, Serial);
}

bool WaitTimesManager::updateData()
{
    // Fetch data from our selected parks/attractions, feeding them
    // into our data structures.

    // For each park...

    // Fetch the data from the web, parsed into JSON
    // Move that into our data structures
    fetchParkWaits("75ea578a-adc8-4116-a54d-dccb60765ef9");

    // Print the result
    serializeJsonPretty(webResponseBuffer, Serial);
    Serial.println();

    return false;
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

