/* 8/5/2021 added serial port check to avoid hang if not connected
 *  also, port 26241 changes on MAC after plugout/in. One case to 26231
 * 7/5/2021 Sketch to display elapsed seconds on the 1.14' display 
 * with alternating background colour.
 * refer to dev device declaration: https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration 
 * for 1.14" TTGO T-Display info
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8
       
#define SerialDebugging true // the 2040 serial hangs if no cu.usbmodem26241 ( on mac ) connection

#include <Arduino_GFX_Library.h>
#define TFT_BL 4
Arduino_DataBus *bus = new Arduino_SWSPI(8 /* DC */, 9 /* CS */, 10 /* SCK */, 11 /* MOSI */, -1 /* MISO */);

Arduino_GFX *tft = new Arduino_ST7789(bus, 12 /* RST */, 1 /* rotation */, true /* IPS */, 135 /* width */, 240 /* height */, 53 /* col offset 1 */, 40 /* row offset 1 */, 52 /* col offset 2 */, 40 /* row offset 2 */);

// color definitions
const uint16_t  Display_Color_Black        = 0x0000;
const uint16_t  Display_Color_Blue         = 0x001F;
const uint16_t  Display_Color_Red          = 0xF800;
const uint16_t  Display_Color_Green        = 0x07E0;
const uint16_t  Display_Color_Cyan         = 0x07FF;
const uint16_t  Display_Color_Magenta      = 0xF81F;
const uint16_t  Display_Color_Yellow       = 0xFFE0;
const uint16_t  Display_Color_White        = 0xFFFF;

// The colors we actually want to use
uint16_t        Display_Text_Color         = Display_Color_Black;
uint16_t        Display_Backround_Color    = Display_Color_Blue;

// declare size of working string buffers. Basic strlen("d hh:mm:ss") = 10
const size_t    MaxString               = 16;

// the string being displayed on the SSD1331 (initially empty)
char oldTimeString[MaxString]           = { 0 };

void displayUpTime() {

    // calculate seconds, truncated to the nearest whole second
    unsigned long upSeconds = millis() / 1000;

    // calculate days, truncated to nearest whole day
    unsigned long days = upSeconds / 86400;

    // the remaining hhmmss are
    upSeconds = upSeconds % 86400;

    // calculate hours, truncated to the nearest whole hour
    unsigned long hours = upSeconds / 3600;

    // the remaining mmss are
    upSeconds = upSeconds % 3600;

    // calculate minutes, truncated to the nearest whole minute
    unsigned long minutes = upSeconds / 60;

    // the remaining ss are
    upSeconds = upSeconds % 60;

    // allocate a buffer
    char newTimeString[MaxString] = { 0 };

    // construct the string representation
    sprintf(
        newTimeString,
        "%lu %02lu:%02lu:%02lu",
        days, hours, minutes, upSeconds
    );

    // has the time string changed since the last tft update?
    if (strcmp(newTimeString,oldTimeString) != 0) {

        // yes! home the cursor
        tft->setCursor(0,0);

        // change the text color to the background color
        tft->setTextColor(Display_Backround_Color);

        // redraw the old value to erase
        tft->print(oldTimeString);

        // home the cursor
        tft->setCursor(0,0);
        
        // change the text color to foreground color
        tft->setTextColor(Display_Text_Color);
    
        // draw the new time value
        tft->print(newTimeString);
    
        // and remember the new value
        strcpy(oldTimeString,newTimeString);
    }
}

void setup() {
 // initialise the display
    tft->begin(); //init(135,240);
    tft->setFont();
    tft->fillScreen(Display_Backround_Color);
    tft->setTextColor(Display_Text_Color);
    tft->setTextSize(4);
    #if (SerialDebugging)
    if(Serial.available()){
    Serial.begin(115200); while (!Serial); Serial.println();
    }
    else
    tft->println("Waiting on comms port connection");
    delay(1000);
    #endif
    // settling time
    delay(250);
}


void loop() {
    tft->fillScreen(Display_Backround_Color);

    displayUpTime();
    delay(1000);
        #if (SerialDebugging)
        Serial.print(millis());
        Serial.println(", display is now runnung ");
        #endif
    tft->fillScreen(Display_Color_Yellow);
    delay(500);
    displayUpTime();
    // no need to be in too much of a hurry
    delay(500);
   
}
