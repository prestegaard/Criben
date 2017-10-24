/*
Name:		LED_TEST.ino
Created:	9/4/2017 3:15:46 PM
Author:	Haagon
*/

#include <FastLED.h>
#include "leds.h"
#include "msgeq7_lauritz.h"
#include "beat.h"
//#include "strip.h"

CRGB leds[NUM_LEDS];

void setup() {
	// tell FastLED there's 50 LED_TYPE leds on pin 9, starting at index 0 in the led array
	FastLED.addLeds<LED_TYPE, 9, COLOR_ORDER>(leds, 0, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	// tell FastLED there's 50 LED_TYPE leds on pin 10, starting at index 50 in the led array
	FastLED.addLeds<LED_TYPE, 10, COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	// tell FastLED there's 50 LED_TYPE leds on pin 11, starting at index 100 in the led array
	FastLED.addLeds<LED_TYPE, 11, COLOR_ORDER>(leds, 2 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	// tell FastLED there's 50 LED_TYPE leds on pin 12, starting at index 150 in the led array
	FastLED.addLeds<LED_TYPE, 12, COLOR_ORDER>(leds, 3 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);

	// Set master brightness control
	FastLED.setBrightness(BRIGHTNESS);
	FastLED.setDither(LED_DITHER);
  
	// Self test
	set_strip(leds, STRIP0, CHSV(HUE_RED, 255, 255));
	delay(300);
	set_strip(leds, STRIP1, CHSV(HUE_BLUE, 255, 255));
	delay(300);
	set_strip(leds, STRIP2, CHSV(HUE_GREEN, 255, 255));
	delay(300);
	set_strip(leds, STRIP3, CHSV(HUE_PINK, 255, 255));
	delay(2000);
		
	// This will set the filter IC ready for reading
	msgeq7_init();

}

uint8_t gHue = 0;

void disco(void) {
	static uint8_t repeat = 0;
	static uint8_t count = 0;
	static uint16_t noBeatCount = 0;
	static uint8_t musicMode = 1;
	static uint8_t on = 0;

	/*if (isBeat()){
	puts("BEAT!!!!!!!!!!!!!!!!!!!!");
	_delay_ms(50);
	strip_setNewHSVColor();
	}*/

	if (count == repeat) {
		repeat = (rand() % 6 + 2) * 4;
		count = 0;
		musicMode = (rand() % 3) + 1;
	}

	switch (musicMode) {
	case 1: //change
		if (isBeat()) {
			count++;
			//strip_setNewHSVColor();
			uint8_t newColor = random(0, 255);
			set_all(leds, CHSV(newColor, 255, 255));
			noBeatCount = 0;
		}
		else {
			noBeatCount++;
		}
		break;
	case 2: //blink
		if (isBeat()) {
			count++;
			noBeatCount = 0;
			//strip_setNewHSVColor();
			uint8_t newColor = random(0, 255);
			set_all(leds, CHSV(newColor, 255, 255));
			_delay_ms(70);
			//strip_setHSV(55555, 55555, 0);
			set_all(leds, CHSV(0, 0, 0));

		}
		else {
			noBeatCount++;
		}
		break;
	case 3: //toggle
		if (isBeat()) {
			count++;
			noBeatCount = 0;
			if (on) {
				//strip_setHSV(55555, 55555, 0);
				set_all(leds, CHSV(0, 0, 0));
				on = 0;
			}
			else {
				on = 1;
				//strip_setNewHSVColor();
				uint8_t newColor = random(0, 255);
				set_all(leds, CHSV(newColor, 255, 255));
			}
			_delay_ms(50);
		}
		else {
			noBeatCount++;
		}
		break;
	}

	if (noBeatCount >= 2048) {
		noBeatCount = 2048;
		//if (strip_fade(256)) {
			//strip_setNewHSVColor();
			set_all(leds, CHSV(gHue, 255, 255));
		//}
	}
}

void loop()
{
	disco();
	EVERY_N_MILLIS(20) { gHue++; }
}