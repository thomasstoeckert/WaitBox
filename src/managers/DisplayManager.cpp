#include "DisplayManager.h"

DisplayManager::DisplayManager() : display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY)
{
    // Do nothing else
}

void DisplayManager::setup()
{
    // Initialize communication with the display
    display.begin(THINKINK_TRICOLOR);

    // Configure into portrait mode
    display.setRotation(1);
}


void DisplayManager::drawSimpleWaits(std::array<ParkWaitTime, 4> waitTimes)
{
    // Clear the buffer
    display.clearBuffer();

    // Margin on x/y axes
    const int MARGIN = 1;
    const int ROW_MARGIN = 4;
    const int TEXT_HEIGHT = 8;

    // Configure text things
    display.setTextSize(1);
    display.setTextColor(EPD_BLACK);
    display.setTextWrap(true);

    int numParks = 4;
    int currentRowNumber = 0;
    for(int i = 0; i < numParks; i++)
    {
        ParkWaitTime park = waitTimes[i];

        // Print park name
        display.setTextColor(EPD_RED);
        display.setCursor(MARGIN, TEXT_HEIGHT * (currentRowNumber++) + MARGIN + i * ROW_MARGIN);
        display.print(park.getName());
        display.setTextColor(EPD_BLACK);

        int overflowLines = park.getName().length() / 21;
        currentRowNumber += overflowLines;

        for (int j = 0; j < park.getNumAttractions(); j++)
        {
            // Get a reference to our attraction
            AttractionWaitTime attr = park.getAttractionWaitTime(j);

            // Draw the label
            display.setCursor(MARGIN, TEXT_HEIGHT * (currentRowNumber++) + MARGIN + i * ROW_MARGIN);
            display.print(attr.getName() + String(" | "));

            int drawnLength = attr.getName().length() + 3;


            // Draw the status / wait
            display.setTextColor(EPD_RED);
            if(attr.getStatus() == "OPERATING")
            {
                display.print(String(attr.getWait()));
                drawnLength += String(attr.getWait()).length();
            } else
            {
                display.print(attr.getStatus());
                drawnLength += attr.getStatus().length();
            }
            
            display.setTextColor(EPD_BLACK);

            // Calculate overflow
            currentRowNumber += drawnLength / 21;
        }
        
        // Draw a dividing line
        if(i != (numParks - 1))
        {
            display.fillRect(1, TEXT_HEIGHT * (currentRowNumber++) + MARGIN + i * ROW_MARGIN + 4, 126, 2, EPD_RED);
        }
    }

    // Draw a little timestamp to the bottom of the display
    display.setCursor(1, 296 - 8);
    display.print(String(millis() / 60000).c_str());

    // Tell the display to update
    display.display();
}

void DisplayManager::drawDummyScreen()
{
    // Clear the buffer
    display.clearBuffer();

    // The margin on x/y axes
    const int MARGIN = 6;
    const int COLUMN_WIDTH = 71;

    const char *labels[] = {
        "Magic Kingdom",
        "EPCOT",
        "DHS",
        "Animal Kingdom"};

    // Draw each column to the buffer
    for (int i = 0; i < 4; i++)
    {
        drawDataColumn(MARGIN, MARGIN + i * COLUMN_WIDTH, labels[i]);
    }

    // Draw a little timestamp to the bottom of the display
    display.setCursor(1, 296 - 8);
    display.print(String(millis() / 60000).c_str());

    // Tell the display to update
    display.display();
}

void DisplayManager::drawDataColumn(int xOffset, int yOffset, const char *label)
{
    const int TEXT_MARGIN = 3;

    // Draw our header label
    display.setFont();
    display.setTextSize(1);
    display.setCursor(xOffset + TEXT_MARGIN, yOffset + TEXT_MARGIN);
    display.setTextColor(EPD_BLACK);
    display.setTextWrap(false);
    display.print(label);

    // Draw the little box underneath
    display.fillRect(xOffset + TEXT_MARGIN, yOffset + TEXT_MARGIN * 2 + 8, 64, 3, EPD_RED);

    // TODO: Draw everything else
}