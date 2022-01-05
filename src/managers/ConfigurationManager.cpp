#include "ConfigurationManager.h"

char ConfigurationManager::configurationString[2048] = "{\"refreshFrequency\":5,\"parks\":[{\"parkID\":\"75ea578a-adc8-4116-a54d-dccb60765ef9\",\"attractions\":[\"352feb94-e52e-45eb-9c92-e4b44c6b1a9d\",\"b2260923-9315-40fd-9c6b-44dd811dbe64\",\"796b0a25-c51e-456e-9bb8-50a324e301b3\",\"a5241f3b-4ab5-4902-b5ba-435132ef553d\",\"9d4d5229-7142-44b6-b4fb-528920969a2c\"]},{\"parkID\":\"47f90d2c-e191-4239-a466-5892ef59a88b\",\"attractions\":[\"480fde8f-fe58-4bfb-b3ab-052a39d4db7c\",\"8d7ccdb1-a22b-4e26-8dc8-65b1938ed5f0\",\"37ae57c5-feaf-4e47-8f27-4b385be200f0\",\"8f353879-d6ac-4211-9352-4029efb47c18\",\"81b15dfd-cf6a-466f-be59-3dd65d2a2807\"]},{\"parkID\":\"288747d1-8b4f-4a64-867e-ea7c9b27bad8\",\"attractions\":[\"1a2e70d9-50d5-4140-b69e-799e950f7d18\",\"6f6998e8-a629-412c-b964-2cb06af8e26b\",\"6e118e37-5002-408d-9d88-0b5d9cdb5d14\",\"34c4916b-989b-4ff1-a7e3-a6a846a3484f\",\"e516f303-e82d-4fd3-8fbf-8e6ab624cf89\"]},{\"parkID\":\"1c84a229-8862-4648-9c71-378ddd2c7693\",\"attractions\":[\"64a6915f-a835-4226-ba5c-8389fc4cade3\",\"24cf863c-b6ba-4826-a056-0b698989cbf7\",\"32e01181-9a5f-4936-8a77-0dace1de836c\",\"55c531b6-3ce2-4c47-a8a1-0dc9107d825b\",\"7a5af3b7-9bc1-4962-92d0-3ea9c9ce35f0\"]}]}";

ConfigurationManager::ConfigurationManager() : fileSystem(&Serial)
{
    // Do nothing - we don't need to initialize anything in our current version
}

bool ConfigurationManager::loadSettings()
{
    // Check our flash config
    if(!fileSystem.checkFlashConfig())
    {
        Serial.println("Flash size was not correct! Pease check your SPIFFS config and try again");
        delay(10000);
        ESP.restart();
    }

    // Allocate our json document
    DynamicJsonDocument configurationDocument(4096);

    // Check to see if configuration data exists in our file system.
    // If it does, load it and parse it as a JSON document.
    if(fileSystem.openFromFile("/config.json", configurationDocument)) 
    {
        // We've loaded and parsed data from the document
        Serial.println("Configuration data loaded from SPIFFS");
        
        // Interpret the JSON document, storing its data in a separate object.
        configurationSettings = ConfigurationSettings(configurationDocument.as<JsonObject>());

        return true;
    }

    // If not, parse the JSON document from our default configuration string.
    DeserializationError dError = deserializeJson(configurationDocument, configurationString);
    if(dError)
    {
        Serial.print("> DeserializedJSON Failed: ");
        Serial.println(dError.c_str());
        configurationSettings = ConfigurationSettings();
        return false;
    }

    Serial.println("Configuration data loaded from default string");

    configurationSettings = ConfigurationSettings(configurationDocument.as<JsonObject>());
    return true;
}

bool ConfigurationManager::saveSettings(String settingString)
{
    // Parse this string as a JSON document
    DynamicJsonDocument configurationDocument(4096);
    DeserializationError error = deserializeJson(configurationDocument, settingString.c_str());

    if(error) 
    {
        Serial.println("Error while parsing config string: ");
        Serial.println(error.c_str());
        return false;
    }

    // If valid, save it to our file system
    fileSystem.saveToFile("/config.json", configurationDocument);

    // And parse it into our configuration settings
    configurationSettings = ConfigurationSettings(configurationDocument.as<JsonObject>());

    // Return true if success, otherwise, false.
    return true;
}

ConfigurationSettings ConfigurationManager::getCurrentSettings()
{
    return configurationSettings;
}