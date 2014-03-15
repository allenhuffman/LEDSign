/*-----------------------------------------------------------------------------
 
 Simple LED Scrolling Message
 By Allen C. Huffman (alsplace@pobox.com)
 www.subethasoftware.com

 This file contains some #defines used by the LEDSign sketch. There are some
 more clever ways to handle much of this, but I wanted some of the code to
 be pretty straight forward and simple. (Even then, some places got a bit
 bogged down anyway.)
 -----------------------------------------------------------------------------*/
 
#define TOPLEFT     0
#define TOPRIGHT    1
#define BOTTOMLEFT  2
#define BOTTOMRIGHT 3

#define STRAIGHT    0
#define ZIGZAG      1

#define DOWN        0
#define UP          1

// These may change. The original idea was to have LEFT/RIGHT be true/false
// opposite to simplify the "ZIGZAG" mode, but instead I chose to do it
// manually so it doesn't relay on the values being 0 and 1.
#define RIGHT       0
#define LEFT        1

/*---------------------------------------------------------------------------*/
// End of LEDSign.h

