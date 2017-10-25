
// leds.h

#ifndef _LEDS_h
#define _LEDS_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


#include <FastLED.h>



#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

#define NUM_STRIPS 4
#define NUM_LEDS_PER_STRIP 50
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

#define BRIGHTNESS         255
#define FRAMES_PER_SECOND  200

#define STRIP0 0
#define STRIP1 49
#define STRIP2 99
#define STRIP3 149
#define UP 1
#define DOWN 0



// Set color functions
void set_strip(CRGB* leds, uint16_t section_start, CHSV color);
void set_all(CRGB* leds, CHSV color);

// Fade color functions
void fade_strip(CRGB* leds, uint16_t section_start, uint16_t delay_time, CHSV color);
void fade_all(CRGB* leds, uint16_t delay_time, CHSV color);

// Fill color functions
void fill_strip(CRGB* leds, uint16_t section_start, uint8_t up_or_down, uint16_t delay_time, CHSV color);
// Show functions
void blink_strip(CRGB* leds, uint16_t section_start, uint16_t delay_time, CHSV color);
void fade_color_upwards(CRGB* leds, uint16_t delay_time, CHSV color);
void fade_color_downwards(CRGB* leds, uint16_t delay_time, CHSV color);
void sinelon(CRGB* leds, CHSV color);
void juggle(CRGB* leds);
#endif

