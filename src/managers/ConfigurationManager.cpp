#include "ConfigurationManager.h"

const char *ConfigurationManager::SELECTED_PARKS[] = {
    "75ea578a-adc8-4116-a54d-dccb60765ef9",
    "47f90d2c-e191-4239-a466-5892ef59a88b",
    "288747d1-8b4f-4a64-867e-ea7c9b27bad8",
    "1c84a229-8862-4648-9c71-378ddd2c7693"};

const char *ConfigurationManager::SELECTED_ATTRACTIONS_1[] = {
    "352feb94-e52e-45eb-9c92-e4b44c6b1a9d",
    "b2260923-9315-40fd-9c6b-44dd811dbe64",
    "796b0a25-c51e-456e-9bb8-50a324e301b3"};

const char *ConfigurationManager::SELECTED_ATTRACTIONS_2[] = {
    "480fde8f-fe58-4bfb-b3ab-052a39d4db7c",
    "8d7ccdb1-a22b-4e26-8dc8-65b1938ed5f0",
    "37ae57c5-feaf-4e47-8f27-4b385be200f0"};

const char *ConfigurationManager::SELECTED_ATTRACTIONS_3[] = {
    "1a2e70d9-50d5-4140-b69e-799e950f7d18",
    "6f6998e8-a629-412c-b964-2cb06af8e26b",
    "6e118e37-5002-408d-9d88-0b5d9cdb5d14"};

const char *ConfigurationManager::SELECTED_ATTRACTIONS_4[] = {
    "64a6915f-a835-4226-ba5c-8389fc4cade3",
    "24cf863c-b6ba-4826-a056-0b698989cbf7",
    "32e01181-9a5f-4936-8a77-0dace1de836c",
};

const char **ConfigurationManager::SELECTED_ATTRACTIONS[] = {
    ConfigurationManager::SELECTED_ATTRACTIONS_1,
    ConfigurationManager::SELECTED_ATTRACTIONS_2,
    ConfigurationManager::SELECTED_ATTRACTIONS_3,
    ConfigurationManager::SELECTED_ATTRACTIONS_4};

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