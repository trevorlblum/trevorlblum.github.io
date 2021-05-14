//routines for demo of ST7789 
void testlines(uint16_t color) {
  tft->fillScreen(BLACK);
  for (int16_t x=0; x < tft->width(); x+=6) {
    tft->drawLine(0, 0, x, tft->height()-1, color);
  }
  for (int16_t y=0; y < tft->height(); y+=6) {
    tft->drawLine(0, 0, tft->width()-1, y, color);
  }
  tft->fillScreen(BLACK);
  for (int16_t x=0; x < tft->width(); x+=6) {
    tft->drawLine(tft->width()-1, 0, x, tft->height()-1, color);
  }
  for (int16_t y=0; y < tft->height(); y+=6) {
    tft->drawLine(tft->width()-1, 0, 0, y, color);
  }
  tft->fillScreen(BLACK);
  for (int16_t x=0; x < tft->width(); x+=6) {
    tft->drawLine(0, tft->height()-1, x, 0, color);
  }
  for (int16_t y=0; y < tft->height(); y+=6) {
    tft->drawLine(0, tft->height()-1, tft->width()-1, y, color);
  }
  tft->fillScreen(BLACK);
  for (int16_t x=0; x < tft->width(); x+=6) {
    tft->drawLine(tft->width()-1, tft->height()-1, x, 0, color);
  }
  for (int16_t y=0; y < tft->height(); y+=6) {
    tft->drawLine(tft->width()-1, tft->height()-1, 0, y, color);
  }
}
void testdrawtext(char *text, uint16_t color) {
  tft->setCursor(0, 0);//seems to  have no effect
  tft->setTextColor(color);
  tft->setTextWrap(true);
  tft->print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft->fillScreen(BLACK);
  for (int16_t y=0; y < tft->height(); y+=5) {
    tft->drawFastHLine(0, y, tft->width(), color1);
  }
  for (int16_t x=0; x < tft->width(); x+=5) {
    tft->drawFastVLine(x, 0, tft->height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft->fillScreen(BLACK);
  for (int16_t x=0; x < tft->width(); x+=6) {
    tft->drawRect(tft->width()/2 -x/2, tft->height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft->fillScreen(BLACK);
  for (int16_t x=tft->width()-1; x > 6; x-=6) {
    tft->fillRect(tft->width()/2 -x/2, tft->height()/2 -x/2 , x, x, color1);
    tft->drawRect(tft->width()/2 -x/2, tft->height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft->width(); x+=radius*2) {
    for (int16_t y=radius; y < tft->height(); y+=radius*2) {
      tft->fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft->width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft->height()+radius; y+=radius*2) {
      tft->drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft->fillScreen(BLACK);
  int32_t color = 0xF800;
  int32_t t;
  int w = tft->width()/2;
  int x = tft->height()-1;
  int y = 0;
  int z = tft->width();
  for(t = 0 ; t <= 15; t++) {
    tft->drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  tft->fillScreen(BLACK);
  uint32_t color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft->width()-2;
    int h = tft->height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft->drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest() {
  tft->setTextWrap(false);
  tft->fillScreen(BLACK);
  tft->setCursor(0,0);
  tft->setTextColor(RED);
  tft->setTextSize(1);
  tft->println("Hello World!");
  tft->setTextColor(YELLOW);
  tft->setTextSize(2);
  tft->println("Hello World!");
  tft->setTextColor(GREEN);
  tft->setTextSize(3);
  tft->println("Hello World!");
  tft->setTextColor(BLUE);
  tft->setTextSize(4);
  tft->print(1234.567);
  delay(pause);
  tft->setCursor(0,50);
  tft->fillScreen(BLACK);
  tft->setTextColor(WHITE);
  tft->setTextSize(0);
  tft->println("Hello World!");
  tft->setTextSize(1);
  tft->setTextColor(GREEN);
  tft->print(p, 6);
  tft->println(" Want pi?");
  tft->println(" ");
  tft->print(8675309, HEX); // print 8,675,309 out in HEX!
  tft->println(" Print HEX!");
  tft->println(" ");
  delay(pause);
  tft->setTextColor(WHITE);
  tft->println("Sketch has been");
  tft->println("running for: ");
  tft->setTextColor(BLUE);
  tft->print(millis() / 1000);
  tft->setTextColor(WHITE);
  tft->print(" seconds.");
  delay(pause*5);
}

void mediabuttons() {
  // play
  tft->fillScreen(BLACK);
  tft->fillRoundRect(25, 10, 78, 60, 8, WHITE);
  tft->fillTriangle(42, 20, 42, 60, 90, 40, RED);
  delay(pause);
  // pause
  tft->fillRoundRect(25, 90, 78, 60, 8, WHITE);
  tft->fillRoundRect(39, 98, 20, 45, 5, GREEN);
  tft->fillRoundRect(69, 98, 20, 45, 5, GREEN);
  delay(pause);
  // play color
  tft->fillTriangle(42, 20, 42, 60, 90, 40, BLUE);
  delay(50);
  // pause color
  tft->fillRoundRect(39, 98, 20, 45, 5, RED);
  tft->fillRoundRect(69, 98, 20, 45, 5, RED);
  // play color
  tft->fillTriangle(42, 20, 42, 60, 90, 40, GREEN);
}
void showcolourmap(){//for color bmp's unpack colours from 16bit integers ref:bitmap_cvt.pde
 //16bits are 5 red, 6 green and 5 blue bits
// Serial.println("In showcolour");
  int x,y,hint;
//  uint32 check=img_ints[0]; //prints 18234 equivalent to 4794.needs to be a far read
//    Serial.println(check);
    for( x=0;x<img_width;x++)
      for( y=0;y<img_height;y++)
    {
        hint=img_ints[x+y*img_width];
// color unpack now done by bitmap_cvt.pde 
        tft->drawPixel(x,y,hint);
     }
}
void unpackbyte(char inbyte,int outint[8]){//for mono bit map bmp's unpack bits from 8 bit bytes
  char res[8];// one bit per char return, 1 or 0
  for( int p=0;p<8;p++)outint[p]=inbyte>>(7-p)&0x01;
}
void showbitmap(int w,int h,int xoff, int yoff){ // unpacks 0xdd format monochrome 0=BLACK 1=WHITE and displays top left corner
// works for 64x64 bitmap signature  
int bits [8];  
 for(int y=0;y<sig_height;y++)
  for(int x=0;x<sig_width/8;x++)
  {
//    Serial.print( pgm_read_byte_near(sig_bits+x+y*sig_width/8));//8 bytes per line
    for(int b=0;b<8;b++){
      unpackbyte( sig_bits[x+y*sig_width/8],bits);
//      Serial.print(" ");Serial.print(bits[b]);
      if(bits[b]==1)tft->drawPixel(xoff+x*8+b,y+yoff,WHITE);else tft->drawPixel(xoff+x*8+b,y+yoff,BLACK);
    }
//    Serial.println();
  }
}
