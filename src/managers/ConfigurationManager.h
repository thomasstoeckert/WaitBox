#include "../models/ConfigurationSettings.h"

class ConfigurationManager 
{
    public:
        ConfigurationManager();

        void loadSettings();

        ConfigurationSettings getCurrentSettings();

    private:
        ConfigurationSettings configurationSettings;
};