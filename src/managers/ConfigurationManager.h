#include <string.h>

class ConfigurationManager 
{
    public:
        ConfigurationManager();

        static const char* SELECTED_PARKS[];
        static const char** SELECTED_ATTRACTIONS[];

        void loadSettings();

    private:
        static const char* SELECTED_ATTRACTIONS_1[];
        static const char* SELECTED_ATTRACTIONS_2[];
        static const char* SELECTED_ATTRACTIONS_3[];
        static const char* SELECTED_ATTRACTIONS_4[];
};