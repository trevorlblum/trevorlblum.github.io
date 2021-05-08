/*******************************************************************************
 * To run in Arduino IDE follow https://www.seeedstudio.com/blog/2021/01/29/arduino-ide-support-announced-for-the-raspberry-pi-pico/
 * to add pico to boards manager.
 * 
 * 'working' Arduino_GFX settings for 1.14" pico pisplay TFT_CS=GPIO9 TFT_RST=GPIO12 TFT_CLK=GPIO10 
*****************************************************************************
 * Arduino_GFX settings as found :
https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration
https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class
https://github.com/moononournation/Arduino_GFX/wiki/Display-Class
******************************************************************************/

#define TFT_DC    GPIO8
#define TFT_RST   GPIO12 
#define TFT_CS    GPIO9 // only for displays with CS pin
#define TFT_MOSI  GPIO11 
#define TFT_SCLK  GPIO10
 
//#include <Arduino_GFX_Library.h>

/* More dev device declaration: https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration */
//#if defined(DISPLAY_DEV_KIT)
//Arduino_GFX *gfx = create_default_Arduino_GFX();
//#else /* !defined(DISPLAY_DEV_KIT) */

#include <Arduino_GFX_Library.h>
#define TFT_BL 4
Arduino_DataBus *bus = new Arduino_SWSPI(8 /* DC */, 9 /* CS */, 10 /* SCK */, 11 /* MOSI */, -1 /* MISO */);

Arduino_GFX *gfx = new Arduino_ST7789(bus, 12 /* RST */, 1 /* rotation */, true /* IPS */, 135 /* width */, 240 /* height */, 53 /* col offset 1 */, 40 /* row offset 1 */, 52 /* col offset 2 */, 40 /* row offset 2 */);

void setup(void)
{
    gfx->begin();
    gfx->fillScreen(BLACK);

#ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
#endif

    gfx->setCursor(10, 10);
    gfx->setTextColor(RED);
    gfx->println("Hello World!");

    delay(5000); // 5 seconds
}

void loop()
{
    gfx->setCursor(random(gfx->width()), random(gfx->height()));
    gfx->setTextColor(random(0xffff), random(0xffff));
    gfx->setTextSize(random(6) /* x scale */, random(6) /* y scale */, random(2) /* pixel_margin */);
    gfx->println("Hello World!");

    delay(1000); // 1 second
}
