#include "AttractionWaitTime.h"

AttractionWaitTime::AttractionWaitTime(const char* inEntityID, const char* inName, const char* inStatus, int inWait) 
{
    // Copy over string data
    entityID = String(inEntityID);
    name     = String(inName);
    status   = String(inStatus);

    // Copy data over for wait
    wait = inWait;
}

AttractionWaitTime::AttractionWaitTime(JsonObject jsonData)
{
    // Check for each piece of data before we attempt to set it
    JsonVariant inputID = jsonData["id"];
    entityID = (!inputID.isNull()) ? String(inputID.as<const char*>()) : String("ID Missing");

    JsonVariant inputName = jsonData["name"];
    name = (!inputName.isNull()) ? String(inputName.as<const char*>()) : String("Name Missing");

    JsonVariant inputStatus = jsonData["status"];
    name = (!inputStatus.isNull()) ? String(inputStatus.as<const char*>()) : String("Status Missing");

    JsonVariant inputWait = jsonData["queue"]["STANDBY"]["waitTime"];
    wait = (!inputWait.isNull()) ? inputWait.as<int>() : -1;
}

String AttractionWaitTime::getEntityID()
{
    return entityID;
}

String AttractionWaitTime::getName()
{
    return name;
}

String AttractionWaitTime::getStatus()
{
    return status;
}

int AttractionWaitTime::getWait()
{
    return wait;
}