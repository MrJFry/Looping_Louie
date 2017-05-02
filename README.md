# Looping_Louie

I always thought that the standard Looping Louie should be more awesome!
Why not add an arduino, a H-bridge and an OLED- Display?

I searched on the internet and everything was lame or required external components.
After a while i found this amazing creation from Great Scott: https://www.youtube.com/watch?v=np6yp-cN6iE

My first thought was: Why couldn't it be without an external box?
So i started thinking how to build something like this and this is what i ended up with:
More details and everything else: http://jannisret.wixsite.com/blog/looping-louie

# Hardware

To build this you need the following parts:

-Looping Louie
-Arduino Nano V3
-128 x 64 Pixel 0,96" OLED Display with I2C (SSD1306)
-L293D H-bridge
-MicroUSB breakout
-tip switch
-wires and some perfboard

## Hardware Setup

Schematics coming soon ;-)

# Software

to use this you have to install the latest arduino IDE and the following libs:

- <Adafruit_GFX> https://github.com/adafruit/Adafruit-GFX-Library
- <Adafruit_SSD1306> https://github.com/adafruit/Adafruit_SSD1306

If the OLED is only half used you have to fix Adafruit_SSD1306.h.
It is located at /USER/documents/Arduino/libraries/Adafruit_SSD1306-master .
Sroll down to the 'SSD1306 Displays' section and choose the Display you are using, in this case *#define SSD1306_128_64*.

## Usage

To use this you only have to plug in the Power and it would start into **Pause Mode**.
When you click the button you can cycle through the modes:
- **Pause Mode**
- **Random Speed Mode**
- **Manual Speed Mode** (fix to 100% Speed because i have not connected an potentiometer)

At the moment there is an issue with the timer in the interrupt, so you have to wait if the time is up in random mode.
I will fix that soon.

## TO DO
- fix the timer issue when switching mode
- add potentiometer
- add real support for the potentiometer
- add countdown in random speed mode
