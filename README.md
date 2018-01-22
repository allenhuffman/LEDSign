LEDSign
=======

Simple scrolling LED Sign for WS2811 (Adafruit NeoPixels). It can easily be
modified to work with LPN8806 or other LED strips with individually addressable
lights. WORK-IN-PROGRESS/DEMO!

It has now been tested with four LED strips, and the logic appears to work.

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
* 2014-03-22 allenh - Added note about being tested on four strips.

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
// Where is LED 0? TOPLEFT, TOPRIGHT, BOTTOMLEFT, or BOTTOMRIGHT
#define LAYOUTSTART    BOTTOMRIGHT
```

* This is where pixel 0 of the LED strips is, based on how the strips are
  laid out. If you started with eight strips with pixel 0 being at the top
  left, this would be TOPLEFT.

```  
// If the strips run one direction, then reverse for the next row,
// use ZIGZAG, else use STRAIGHT.
#define LAYOUTMODE     STRAIGHT
```

* The LED strips I have daisy chain from one to the next, so if you plan to
  use multiple strips that will zig zag back and forth, setting this to
  ZIGZAG will reverse the pixel rendering on every other line so it all shows
  up correctly. If you are wiring the LEDs so each row goes the same
  direction (0-59 on the first row, left to right, then 60-119 on the next
  row, left to right, etc.), this can be STRAIGHT. (There is much code out
  there that requires the LEDs to be wired that way. I wanted mine to work
  in the easier way I plan to wire mine up.)

```
#define SCROLLSPEED    100 // 100ms (1000=1 second)
```

* After each frame is drawn, a delay(x) of this long will be done before the
  display shifted a pixel to the left and continues.
  
```
// If defined, a strip.setBrightness(x) will be done. I use this so more
// LEDs can be powered off an Arduino supply if they are all very dim/low
// power. You should be using a proper power supply, however!
#define LEDBRIGHTNESS  2
```

* The NeoPixel library supports a setBrightness(x) function, so if this
  #define is set, it will call that function with the value. I just put this
  here so it is easier to change. Eventually, it will be a settable parameter
  from the serial interface. (NOTE: I only have two strips, and run them off
  the Arduino power pins. There is *NOT* enough power to run more than 3-4
  dozen LEDs at the same time, so I dropped the brightnes way down hoping
  to use less power so I could do more testing. You should use a real power
  supply. Don't do what I did.)
  
```
// Specify which font to use. (These examples are for the TVout fonts.)
//const unsigned char *font = font4x6;
const unsigned char *font = font6x8;
//const unsigned char *font = font8x8; // Blank row on top. Bad font.
//const unsigned char *font = font8x8ext;
````

* These are the TVout fonts. I just set *font to point to whichever one I want
  to use. The 8x8 font is different from the rest. It skips the first row of
  each character leaving a gap at the top, while all the other fonts start at
  the top row. I don't like that. I plan to replace all the fonts with much
  more appropriate ones for LED scrolling sign use. But for now, this is what
  I had and I just put this together in an evening to test it.
  
```
// Set these defines to match the font data, or, if using the TVout
// fonts, these values can be read from the first three bytes of
// the file (and FONTDATAOFFSET is set to skip those first three
// bytes).
#define FONTWIDTH      (pgm_read_byte_near(&font[0]))
#define FONTHEIGHT     (pgm_read_byte_near(&font[1]))
#define FONTSTARTCHAR  (pgm_read_byte_near(&font[2]))
#define FONTDATAOFFSET 3
```

* The TVout fonts are just arrays of bytes, but the first three bytes serve
  as a header to describe the font. The first byte is the width of the font,
  and the second is the height. The third byte is the first character that
  the font represents. Most fonts start at 32 (space) so that would be a 32,
  but some might put characters in the non-printable region (characters 0-31)
  so that value might be a 0. If you use a font that is just raw data, you
  could just set the FONTWIDTH and FONTHEIGHT manually, and then set the
  FONTDATAOFFSET to 0 (if there was no header information at the start). I
  just wanted this to be flexible, since I don't plan to keep using the
  TVout fonts. In the 90s, I wrote and sold a banner printing program and it
  was loaded with TONS of 8-bit fonts that I plan to use in this program
  eventually.
  
I think that is all you need to configure, but everything is commented in case
I missed something. Like "DEBUG". If that is defined, the Serial console will
draw out "X" and " " to represent where the LEDs are being set on each LED
strip. They are printed as if each strip runs the same direction (STRAIGHT
mode), so if you are using ZIGZAG or other options, it may be printing what
looks like scrambled text or upside down/backwards text. That is because it
is sending that out to the LEDs that way, and the arrangemnet of the LEDs
makes it look proper. Hopefully.

RUNNING
=======
 
 The Serial console will ask for input (a short 80 byte message) and then
 scroll it. Nothing fancy. Yet.
 
 More to come...
 

