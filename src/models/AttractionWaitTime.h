#include <ArduinoJson.h>

class AttractionWaitTime
{
    public:
        // Constructors
        AttractionWaitTime(const char* inEntityID, const char* inName, const char* inStatus, int inWait);
        AttractionWaitTime(JsonObject jsonData);
        
        // Getters
        String getEntityID();
        String getName();
        String getStatus();
        int   getWait();

    private:
        String entityID;
        String name;
        String status;
        int wait;
};