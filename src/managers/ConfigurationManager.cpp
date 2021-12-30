#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager()
{
    // Do nothing - we don't need to initialize anything in our current version
}

void ConfigurationManager::loadSettings()
{
    // Do nothing - we don't need to load anything in our current version
    configurationSettings = ConfigurationSettings();
}

ConfigurationSettings ConfigurationManager::getCurrentSettings()
{
    return configurationSettings;
}