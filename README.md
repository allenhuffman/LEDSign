LEDSign
=======

Simple scrolling LED Sign for WS2811 (Adafruit NeoPixels). It can easily be
modified to work with LPN8806 or other LED strips with individually addressable
lights. WORK-IN-PROGRESS/DEMO!

===============================================================================

This code is designed to work with the Adafruit_NeoPixel library:

https://github.com/adafruit/Adafruit_NeoPixel

It also uses the TVout fonts since those were what I had available:

https://code.google.com/p/arduino-tvout/

If you have both of those libraries installed, the code should compile and run
for NeoPixel / WS2811 LED strips. The LED setup functions could be changed
to work with a different type of strip, and the set and unset LED functions
could be modified as well. Basically, any strip of LEDs that can be set by
number 0-max could be made to work.

The LED libraries have their own limitations with memory, so the total number
of LEDs that can be used on an Arduino UNO might be around 500 or so. I have
some plans to alter or rewrite the LED library to get past this limitation.

See my original articles:

http://subethasoftware.com/2014/03/15/simple-scrolling-led-sign-for-neopixel-ws2811-or-lpn8806/

REVISION
========
* 2014-03-14 allenh - Initial, hastily created README file.
* 2014-03-09 allenh - Adding link to my original article.

FILES
=====

* README.md - this file
* LEDSign.ino
* LEDSign.h
* LineInput.ino - console input routine with line length limit.

CONFIGURATION
=============

Edit the LEDSign.ino as appropriate:

```
// Adafruit NeoPixel library configuration.
#define PIN            6
```

* This is the data pin used by the NeoPixel library.
  
```
// LED strip configuration.
// Example: 7 1m 60-LED strips (similar to BetaBrite 80x7 display).
#define LEDSTRIPS      7
#define LEDSPERSTRIP   60
#define LEDSPERROW     60
```

* These describe the number of strips in use and how many LEDs each one has.
  The LEDSPERROW is how many LEDS are in each row of the sign. If you made a
  sign of eight 60 LED strips, with one strip per row, that would be 60.
  I created a small circular sign by taking a few strips and rotating them in
  a spiral so everything lined up, and used other values (commented out in the
  source code) to do that.

```  
// LED strip layout.
// Where is LED 0? TOPLEFT, TOPRIGHT, BOTTOMLEFT, or 
