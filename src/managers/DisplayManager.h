#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ThinkInk.h>
#include <array>

#include "../models/ParkWaitTime.h"

#define EPD_DC    26  // Pin 26 - [Out] Data / Command pin on display
#define EPD_CS    27  // Pin 27 - [Out] Display Chip Select
#define EPD_BUSY  33  // Pin 33 - [In]  Display Busy Line
#define EPD_RESET 32  // Pin 32 - [Out] Display Reset

#define SRAM_CS   25  // Pin 25 - [Out] SRAM Chip Select

class DisplayManager 
{
    public:
        DisplayManager();
        void setup();

        void drawDummyScreen();
        void drawSimpleWaits(std::array<ParkWaitTime, 4> waitTimes);

    private:
        ThinkInk_290_Tricolor_Z10 display;

        void drawDataColumn(int xOffset, int yOffset, const char* label);
};