/* 1.14" display on pico 2040. Running 13/5/2021
 * derived from adafruit demo ported to pi-Pico 2040 
 * requires demo-routines.h, flower.h and signature,h (tlb's sig face )
 ****************************************************/
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <SPI.h>
#include <Arduino_GFX_Library.h>

#define TFT_DC    8
#define TFT_RST   9 
#define TFT_CS    10 // only for displays with CS pin
#define TFT_MOSI  4//11   // for hardware SPI data pin (all of available pins)
#define TFT_SCLK  5//13   // for hardware SPI sclk pin (all of available pins)
#include "signature.h" //tlb face icon
#include "flower.h"  

#define ButtonR 13
#define ButtonM 14
#define ButtonL 12
#define TFT_BL 4

Arduino_DataBus *bus=new Arduino_SWSPI(8 /*DC*/,9 /*CS*/,10 /*SCK*/,11 /*MOSI*/,-1 /*MISO*/);
Arduino_GFX *tft = new Arduino_ST7789(bus, 12 /* RST */, 1 /* rotation */, true /* IPS */, 135 /* width */, 240 /* height */, 53 /* col offset 1 */, 40 /* row offset 1 */, 52 /* col offset 2 */, 40 /* row offset 2 */);const size_t MaxString = 16;

float p = 3.1415926;
int loopcount=0;
int pause=500;

#define BGLed 16 

#include "demo_routines.h" // has to follow global definitions of tft, for example

void setup(void) {
  pinMode(ButtonR,INPUT_PULLUP);
  pinMode(ButtonM,INPUT_PULLUP);
  pinMode(ButtonL,INPUT_PULLUP);
  digitalWrite(BGLed,HIGH);delay(1000);digitalWrite(BGLed,LOW);//related to WDT disable???
  Serial.begin(9600);
  Serial.print("Hello! ST7789 TFT Test");
  tft->begin();   // initialize a ST7789 chip, 240x135 pixels//SPI_MODEs not relevant
  Serial.println("Initialized");
  Serial.println(sizeof(sig_bits));
  uint16_t time = millis();
  tft->fillScreen(BLACK);
  time = millis() - time;
  Serial.print("Screen fill time (msecs)");
  Serial.println(time, DEC);
  Serial.println(0x084794);
  for(int chk=0;chk<10;chk++)Serial.println(img_ints[chk]);
//  Serial.print("RED,GREEN,BLUE ");
//  Serial.print(RED);Serial.print(" ");Serial.print(GREEN);Serial.print(" ");Serial.print(BLUE);
 uint32_t ct,rt,gt,bt,tt;
        tt=0x0FFFFFF;
        rt=tt&0xF800;//8 to 5bits
        gt=tt&0x07E0;//8 to 6bits
        bt=tt&0x01F;//8 to 5bits
tft->begin();
tft->setFont();
tft->setTextColor(0x0FFFF);//white
        tft->fillScreen(tt&0xF800);//RED
        tft->fillScreen(tt&0x7E0); //GREEN
        tft->fillScreen(tt&0x1F);  //BLUE
        tft->fillScreen(rt|gt|bt);
        delay(pause);
        tft->fillScreen(0x0FFFF);          
        delay(pause);
        tft->fillScreen(BLACK);

showbitmap(sig_width,sig_height,100,50);delay(2000); //for mono bmp's
showcolourmap();delay(2000);                       //for colour bmp's
}
void loop() {
  tft->begin();
  // large block of text - doubled with line feeds tlb
  tft->setCursor(0,0);
  tft->fillScreen(BLACK);
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. \nCurabitur adipiscing ante sed nibh tincidunt feugiat.\nMaecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. \nSed porttitor neque ut ante pretium vitae  malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. \n\nLorem ipsum dolor sit amet, consectetur adipiscing elit. \nCurabitur adipiscing ante sed nibh tincidunt feugiat.\nMaecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. \nSed porttitor neque ut ante pretium vitae  malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", WHITE);
  delay(pause);
 // tft print function - OK
  tftPrintTest();
  delay(pause); 
  // line draw test - OK 
  testlines(YELLOW);
  delay(pause);
  // optimized lines - ok
  testfastlines(RED, BLUE); 
  delay(pause);
  tft->begin();//tlb
  testdrawrects(GREEN); 
  delay(pause);
  testfillrects(YELLOW,BLACK);//MAGENTA); 
  delay(pause);
  tft->fillScreen(BLACK);
  testfillcircles(10, BLUE); 
  testdrawcircles(10, WHITE); 
  delay(pause);
  testroundrects();
  delay(pause);
  testtriangles();
  delay(pause);
  tft->fillScreen(BLACK);
  for(int r=0;r<5;r++)
    for(int i=0;i<10;i++){tft->drawPixel(random(tft->width()), random(tft->height()), GREEN);
    for(int i=0;i<10;i++)tft->drawPixel(random(tft->width()), random(tft->height()), GREEN);
    delay(50);
  }
  mediabuttons();
  delay(100);
  loopcount++;Serial.print("Loop Number ");
  Serial.println(loopcount);
  if(digitalRead(ButtonM)==LOW){
    tft->invertDisplay(true);
    testtriangles();
    delay(100);
    mediabuttons();
    }
  for(int i=0;i<10;i++){  
  tft->invertDisplay(true);
  delay(100);
  tft->invertDisplay(false);
  delay(100);
  }
  tft->invertDisplay(true);
  tft->fillScreen(BLACK);
  showbitmap(sig_width,sig_height,100,50);delay(2000); //for mono bmp's
}
