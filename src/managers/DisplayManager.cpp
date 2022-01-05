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

void DisplayManager::drawWaits(std::vector<ParkWaitTime> waitTimes)
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
    display.setTextWrap(false);

    int numParks = waitTimes.size();
    int currentRowNumber = 1;
    for (int i = 0; i < numParks; i++)
    {
        ParkWaitTime park = waitTimes[i];

        // Print park name
        display.setTextColor(EPD_RED);
        display.setCursor(MARGIN, TEXT_HEIGHT * (currentRowNumber++) + MARGIN + i * ROW_MARGIN);
        display.print(park.getName());
        display.setTextColor(EPD_BLACK);

        // Park names get an extra row as a treat.
        currentRowNumber++;

        for (int j = 0; j < park.getNumAttractions(); j++)
        {
            // Get a reference to our attraction
            AttractionWaitTime attr = park.getAttractionWaitTime(j);

            drawAttraction(attr, MARGIN, TEXT_HEIGHT * (currentRowNumber++) + MARGIN + i * ROW_MARGIN);
        }

        // Draw a dividing line
        if (i != (numParks - 1))
        {
            display.fillRect(1, TEXT_HEIGHT * (currentRowNumber++) + MARGIN + i * ROW_MARGIN + 4, 126, 2, EPD_RED);
        }
    }

    // Draw a little timestamp to the bottom of the display
    display.setCursor(1, 296 - 8);
    display.print("up: ");
    display.print(String(millis() / 60000).c_str());
    display.print(" minutes");

    // Tell the display to update
    display.display();
}

void DisplayManager::drawAttraction(AttractionWaitTime attr, int x, int y)
{
    // Move our cursor to this position
    display.setCursor(x, y);

    // First: Draw the wait time or status of the attraction, limited to three
    // characters.

    display.setTextColor(EPD_RED);
    if (attr.getStatus() == "OPERATING" && attr.getWait() > 0)
    {
        // If the attraction is operating, the important info is its wait time.
        // Get it, and if it's too short, pad it on the left side.

        String timeString = String(attr.getWait());
        if (timeString.length() < 3)
        {
            int toPad = 3 - timeString.length();

            for (int k = 0; k < toPad; k++)
            {
                timeString = " " + timeString;
            }
        }

        display.print(timeString);
    }
    else
    {
        // If the attraction is not operating, we want to convey why. Different
        // reasons have differing levels of importance.

        // If the attraction is DOWN, this means its regular operation has been
        // interrupted. It's important to show this.
        String status = attr.getStatus();
        if (status == "DOWN")
        {
            status = "DWN";
        }
        else
        {
            status = "---";
        }

        display.print(status);
    }
    display.setTextColor(EPD_BLACK);

    // Draw our spacer
    display.print("|");

    // Draw the label
    display.print(attr.getName());
}