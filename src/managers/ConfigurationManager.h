#include "../models/ConfigurationSettings.h"

#include <ArduinoJson.h>
#include <Effortless_SPIFFS.h>

class ConfigurationManager 
{
    public:
        ConfigurationManager();

        bool loadSettings();
        bool saveSettings(String settingString);

        ConfigurationSettings getCurrentSettings();

        static char configurationString[2048];

    private:
        ConfigurationSettings configurationSettings;
        eSPIFFS fileSystem;
};