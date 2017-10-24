/*
Name:		LED_TEST.ino
Created:	9/4/2017 3:15:46 PM
Author:	Haagon
*/

#include <FastLED.h>
#include "leds.h"


CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];


void setup() {
	delay(3000); // 3 second delay for recovery

	// tell FastLED there's 50 NEOPIXEL leds on pin 9, starting at index 0 in the led array
	FastLED.addLeds<LED_TYPE, 9, COLOR_ORDER>(leds, 0, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	// tell FastLED there's 50 LED_TYPE leds on pin 10, starting at index 50 in the led array
	FastLED.addLeds<LED_TYPE, 10, COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	// tell FastLED there's 50 LED_TYPE leds on pin 11, starting at index 100 in the led array
	FastLED.addLeds<LED_TYPE, 11, COLOR_ORDER>(leds, 2 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	// tell FastLED there's 50 LED_TYPE leds on pin 12, starting at index 150 in the led array
	FastLED.addLeds<LED_TYPE, 12, COLOR_ORDER>(leds, 3 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);

	// set master brightness control
	FastLED.setBrightness(BRIGHTNESS);

  red();
  FastLED.show();
}

uint8_t gHue = 0;
// the loop function runs over and over again until power down or reset
void loop() {
	// Set each section with same color
//	set_section(leds, STRIP0, NUM_LEDS_PER_STRIP, CHSV(gHue, 255, 255));
//	delay(200);
//	set_section(leds, STRIP1, STRIP1 + NUM_LEDS_PER_STRIP, CHSV(gHue, 255, 255));
//	delay(200);
//	set_section(leds, STRIP2, STRIP2 + NUM_LEDS_PER_STRIP, CHSV(gHue, 255, 255));
//	delay(200);
//	set_section(leds, STRIP3, STRIP3 + NUM_LEDS_PER_STRIP, CHSV(gHue, 255, 255));
//	
//	delay(2000);

//	// Fill each section with different color upwards
//	gHue += 50;
//	fill_section(leds, STRIP0, STRIP0 + NUM_LEDS_PER_STRIP, 10, CHSV(gHue, 255, 255));
//	delay(200);

//	gHue += 50;
//	fill_section(leds, STRIP1, STRIP1 + NUM_LEDS_PER_STRIP, 10, CHSV(gHue, 255, 255));
//	delay(200);

//	gHue += 50;
//	fill_section(leds, STRIP2, STRIP2 + NUM_LEDS_PER_STRIP, 10, CHSV(gHue, 255, 255));
//	delay(200);


//	gHue += 50;
//	fill_section(leds, STRIP3, STRIP3 + NUM_LEDS_PER_STRIP, 10, CHSV(gHue, 255, 255));
//	delay(200);

//	// Run some sinelon loop
//	sinelon(leds, CHSV(gHue, 255, 255));

//	// Fade whole pyramide into new color
//	fade_all(leds, 20, CHSV(gHue, 255, 255));
//	delay(2000);
//	gHue += 50;
//	
//	juggle(leds);
	
	//FastLED.show();
	// insert a delay to keep the framerate modest
	//FastLED.delay(1000 / FRAMES_PER_SECOND);
	//rainbow();

	//// do some periodic updates
	//if (!sensor_changed_to_low)
	//{
	EVERY_N_MILLISECONDS(20) { gHue++; } // slowly cycle the "base color" through the rainbow

}

void rainbow(){
	uint8_t color = gHue;
	for(uint8_t i = 0; i<50; i++){
		leds[i] = CHSV(color, 255, 255);
		leds[i + 49] = CHSV(color, 255, 255);
		leds[i + 99] = CHSV(color, 255, 255);
		//leds[i + 149] = CHSV(color, 255, 255);
    color += 5;
	}
}

void red(){
  for(uint8_t i = 0; i<50; i++){
    leds[i] = CHSV(0, 255, 255);
    leds[i + 49] = CHSV(0, 255, 255);
    leds[i + 99] = CHSV(0, 255, 255);
    leds[i + 149] = CHSV(0, 255, 255);
 
  }
 
}
