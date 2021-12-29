#include "../models/ConfigurationSettings.h"

class ConfigurationManager 
{
    public:
        ConfigurationManager();

        static const char* SELECTED_PARKS[];
        static const char** SELECTED_ATTRACTIONS[];

        void loadSettings();

        ConfigurationSettings getCurrentSettings();

    private:
        ConfigurationSettings configurationSettings;

        static const char* SELECTED_ATTRACTIONS_1[];
        static const char* SELECTED_ATTRACTIONS_2[];
        static const char* SELECTED_ATTRACTIONS_3[];
        static const char* SELECTED_ATTRACTIONS_4[];
};