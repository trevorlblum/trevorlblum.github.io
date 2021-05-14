This 4-file group covers porting of the Adafruit graphics demo to the pi_Pico 2040.

Included with the 1_14_demo.ino Arduino source are the demo_routines needed to do the grunt and two image files, flower.h and signature.h used for RGB graphics images.

Signature.h is a monochrome ( one-bit ) image. flower.h is a .BMP colour 24-bit RGB image which is scaled down to the 16 bit (5 Red,6 Green,5 Blue)display format for the 1_14 device.
