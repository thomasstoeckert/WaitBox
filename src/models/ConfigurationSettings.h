#pragma once

#include <Arduino.h>

class ConfigurationSettings
{
    public:
        ConfigurationSettings();

        bool getShowAttractions();
        bool getShowShows();
        bool getShowOthers();

        int getNumParks();
        String getSelectedParkID(int parkIndex);
        
        std::vector<String> getAttractionFilterForPark(int parkIndex);
    private:
        bool showAttractions;
        bool showShows;
        bool showOthers;

        std::vector<String> parkFilters;
        std::vector<std::vector<String>> attractionFilters;
};