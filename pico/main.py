#main.py trial
from ssd1306 import SSD1306_I2C
from machine import Pin,SoftI2C
import framebuf
import time

led=Pin(25,Pin.OUT)
led.toggle()

i2c=SoftI2C(scl=9,sda=8)#default init
oled=SSD1306_I2C(128,64,i2c)
# Raspberry Pi logo as 32x32 bytearray
buffer = bytearray(b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00|?\x00\x01\x86@\x80\x01\x01\x80\x80\x01\x11\x88\x80\x01\x05\xa0\x80\x00\x83\xc1\x00\x00C\xe3\x00\x00~\xfc\x00\x00L'\x00\x00\x9c\x11\x00\x00\xbf\xfd\x00\x00\xe1\x87\x00\x01\xc1\x83\x80\x02A\x82@\x02A\x82@\x02\xc1\xc2@\x02\xf6>\xc0\x01\xfc=\x80\x01\x18\x18\x80\x01\x88\x10\x80\x00\x8c!\x00\x00\x87\xf1\x00\x00\x7f\xf6\x00\x008\x1c\x00\x00\x0c \x00\x00\x03\xc0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00")

# Load the raspberry pi logo into the framebuffer (the image is 32x32)
fb = framebuf.FrameBuffer(buffer, 32, 32, framebuf.MONO_HLSB)

# Clear the oled display in case it has junk on it.
oled.fill(0)

# Blit the image from the framebuffer to the oled display
oled.blit(fb, 96, 0)
oled.ellipse(60,55,8,8,1,1)
# Add some text
oled.text("Raspberry Pi",5,5)
oled.text("Pico",5,15)
oled.text("Main.py running",1,35)
# Finally update the oled display so the image & text is displayed
for i in range(10):
    led.toggle()
    oled.invert(1)
    oled.show()
    time.sleep(.1)
    oled.invert(0)
    oled.show()
    time.sleep(.1)
oled.fill(0)    
oled.text("Main.py ended",10,32)
oled.show()