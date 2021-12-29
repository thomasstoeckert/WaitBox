#include "ConfigurationSettings.h"

ConfigurationSettings::ConfigurationSettings()
{
    // Establish default configuration settings
    showAttractions = true;
    showShows = false;
    showOthers = false;

    // Set our attraction filters <TEMPORARY>
    numFilters = 3;
    filters.push_back("352feb94-e52e-45eb-9c92-e4b44c6b1a9d");
    filters.push_back("b2260923-9315-40fd-9c6b-44dd811dbe64");
    filters.push_back("796b0a25-c51e-456e-9bb8-50a324e301b3");
}

bool ConfigurationSettings::getShowAttractions()
{
    return showAttractions;
}

bool ConfigurationSettings::getShowShows()
{
    return showShows;
}

bool ConfigurationSettings::getShowOthers()
{
    return showOthers;
}

int ConfigurationSettings::getNumFilters()
{
    return numFilters;
}

String ConfigurationSettings::getFilter(int i)
{
    return filters[i];
}