#include <ArduinoJson.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#include "../models/ParkWaitTime.h"
#include "../models/AttractionWaitTime.h"
#include "../models/ConfigurationSettings.h"

class WaitTimesManager
{
public:
    WaitTimesManager();
    void init();
    bool updateData(ConfigurationSettings configSettings);
    std::vector<ParkWaitTime> getWaitTimes();

private:
    // This larger JSON document holds the responses from our web requests
    // We only keep one at a time, but, it's still pretty big. As such, is
    // kept in dynamic memory.
    DynamicJsonDocument webResponseBuffer;

    // Our results filter for attraction responses is small, constant, and
    // used pretty much everywhere.
    StaticJsonDocument<256> attractionResultFilter;

    // WaitTimes Cache
    std::vector<ParkWaitTime> parkWaitTimes;

    // Utility Functions
    bool fetchParkWaits(const char* parkID);


    // Constant Values
    static constexpr const char* baseURL = "https://api.themeparks.wiki/v1/";
    static constexpr const char* slugEntities = "destinations";
    static constexpr const char* slugEntity = "entity/";
    static constexpr const char* slugLive ="/live";
    static constexpr const char* headerKeys[] = {"Location", "Date", "Content-Type", "Server", "cf-ray"};
    static constexpr const char* FILTER_STRING = R""""({"name": true, "liveData": [{"id": true, "name": true, "entityType": true, "status": true, "queue": {"STANDBY": true}]})"""";


    // Our HTTPS Certificate
    static constexpr const char *root_ca = R""""(
-----BEGIN CERTIFICATE-----
MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJ
RTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYD
VQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoX
DTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMCSUUxEjAQBgNVBAoTCUJhbHRpbW9y
ZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFsdGltb3JlIEN5YmVy
VHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKMEuyKr
mD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjr
IZ3AQSsBUnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeK
mpYcqWe4PwzV9/lSEy/CG9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSu
XmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9XbIGevOF6uvUA65ehD5f/xXtabz5OTZy
dc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjprl3RjM71oGDHweI12v/ye
jl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoIVDaGezq1
BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3
DQEBBQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT92
9hkTI7gQCvlYpNRhcL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3Wgx
jkzSswF07r51XgdIGn9w/xZchMB5hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0
Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsaY71k5h+3zvDyny67G7fyUIhz
ksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9HRCwBXbsdtTLS
R9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp
-----END CERTIFICATE-----
)"""";
};