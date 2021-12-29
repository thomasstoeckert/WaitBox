#pragma once

#include <Arduino.h>

class ConfigurationSettings
{
    public:
        ConfigurationSettings();

        bool getShowAttractions();
        bool getShowShows();
        bool getShowOthers();
        int getNumFilters();

        String getFilter(int i);
    private:
        bool showAttractions;
        bool showShows;
        bool showOthers;
        int numFilters;
        std::vector<String> filters;
};