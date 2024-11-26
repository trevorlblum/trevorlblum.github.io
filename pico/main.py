#main.py trial
#26/11/2024 added oled2 on 5,4 to oled on 9,8. Checks for ssd1306_2 present
#NOTE: the ssd1306 displays are both default 03xC, no jumper change needed ( different scl/sda pins).
from ssd1306 import SSD1306_I2C
from machine import Pin,SoftI2C
import framebuf
import time


def oleds(oled):  
    # Clear (black fill) the oled display in case it has junk on it.
    oled.fill(0)
    # Blit the image from the framebuffer to the first oled display
    oled.blit(fb, 96, 0)
    oled.ellipse(60,55,8,8,1,1)
    # Add some text
    oled.text("Raspberry Pi",5,5)
    oled.text("Pico",5,15)
    oled.text("Main.py running",1,35)
    # flash the onboard led - useful to know it is alive if the ssd1306s are blank
    for i in range(10):
        led.toggle()
        oled.invert(1)
        oled.show()
        time.sleep(.25)
        oled.invert(0)
        oled.show()
    time.sleep(.25)
    oled.fill(0)
    oled.text("ssd1306 DONE",10,32)
    # Finally update the oled display so the image & text is displayed
    oled.show()

#Main code block
led=Pin(25,Pin.OUT)
led.toggle()

i2c1=SoftI2C(scl=9,sda=8)#default init
oled1=SSD1306_I2C(128,64,i2c1)

i2c2=SoftI2C(scl=5,sda=4)#second ssd1306

# Raspberry Pi logo as 32x32 bytearray
buffer = bytearray(b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00|?\x00\x01\x86@\x80\x01\x01\x80\x80\x01\x11\x88\x80\x01\x05\xa0\x80\x00\x83\xc1\x00\x00C\xe3\x00\x00~\xfc\x00\x00L'\x00\x00\x9c\x11\x00\x00\xbf\xfd\x00\x00\xe1\x87\x00\x01\xc1\x83\x80\x02A\x82@\x02A\x82@\x02\xc1\xc2@\x02\xf6>\xc0\x01\xfc=\x80\x01\x18\x18\x80\x01\x88\x10\x80\x00\x8c!\x00\x00\x87\xf1\x00\x00\x7f\xf6\x00\x008\x1c\x00\x00\x0c \x00\x00\x03\xc0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00")

# Load the raspberry pi logo into the framebuffer (the image is 32x32)
fb = framebuf.FrameBuffer(buffer, 32, 32, framebuf.MONO_HLSB)

oleds(oled1) #run oled1 - assumed always present

try:
    oled2=SSD1306_I2C(128,64,i2c2)
except:
    print("No second device detected")
else:
    oleds(oled2) # run oled2 if present
    
