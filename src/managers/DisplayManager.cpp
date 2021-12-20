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