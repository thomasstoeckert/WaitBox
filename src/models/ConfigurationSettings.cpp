#include "ConfigurationSettings.h"

ConfigurationSettings::ConfigurationSettings()
{
    // Establish default configuration settings
    showAttractions = true;
    showShows = false;
    showOthers = false;

    // Create our park filters
    parkFilters.push_back("75ea578a-adc8-4116-a54d-dccb60765ef9");
    parkFilters.push_back("47f90d2c-e191-4239-a466-5892ef59a88b");
    parkFilters.push_back("288747d1-8b4f-4a64-867e-ea7c9b27bad8");
    parkFilters.push_back("1c84a229-8862-4648-9c71-378ddd2c7693");

    // Set our attraction filters <TEMPORARY>
    // Create filter for Park 1
    std::vector<String> park1Vector, park2Vector, park3Vector, park4Vector;
    park1Vector.push_back("352feb94-e52e-45eb-9c92-e4b44c6b1a9d");
    park1Vector.push_back("b2260923-9315-40fd-9c6b-44dd811dbe64");
    park1Vector.push_back("796b0a25-c51e-456e-9bb8-50a324e301b3");

    // Create filter for Park 2
    park2Vector.push_back("480fde8f-fe58-4bfb-b3ab-052a39d4db7c");
    park2Vector.push_back("8d7ccdb1-a22b-4e26-8dc8-65b1938ed5f0");
    park2Vector.push_back("37ae57c5-feaf-4e47-8f27-4b385be200f0");

    // Create filter for Park 3
    park3Vector.push_back("1a2e70d9-50d5-4140-b69e-799e950f7d18");
    park3Vector.push_back("6f6998e8-a629-412c-b964-2cb06af8e26b");
    park3Vector.push_back("6e118e37-5002-408d-9d88-0b5d9cdb5d14");

    // Create filter for Park 4
    park4Vector.push_back("64a6915f-a835-4226-ba5c-8389fc4cade3");
    park4Vector.push_back("24cf863c-b6ba-4826-a056-0b698989cbf7");
    park4Vector.push_back("32e01181-9a5f-4936-8a77-0dace1de836c");

    // Push all filters into the master filter
    attractionFilters.push_back(park1Vector);
    attractionFilters.push_back(park2Vector);
    attractionFilters.push_back(park3Vector);
    attractionFilters.push_back(park4Vector);
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

std::vector<String> ConfigurationSettings::getAttractionFilterForPark(int parkIndex)
{
    return attractionFilters[parkIndex];
}

int ConfigurationSettings::getNumParks()
{
    return parkFilters.size();
}

String ConfigurationSettings::getSelectedParkID(int parkIndex)
{
    return parkFilters[parkIndex];
}