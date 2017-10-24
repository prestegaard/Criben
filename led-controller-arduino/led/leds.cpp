// 
// 
// 

#include "leds.h"


// Set color functions
void set_strip(CRGB * leds, uint16_t section_start, CHSV color)
{
	for (uint16_t i = section_start; i <= section_start + NUM_LEDS_PER_STRIP; i++)
	{
		leds[i] = color;
	}
	FastLED.show();
}

void set_all(CRGB * leds, CHSV color)
{
	for (uint16_t i = 0; i < NUM_LEDS; i++)
	{
		leds[i] = color;
	}
	FastLED.show();
}

// Fill color functions
void fade_strip(CRGB * leds, uint16_t section_start, uint16_t delay_time, CHSV color)
{
	for (uint16_t i = 0; i < 255; i++)
	{
		set_strip(leds, section_start, CHSV(color.hue, color.sat, i));
		delay(delay_time);
	}
}

void fade_all(CRGB * leds, uint16_t delay_time, CHSV color)
{
	for (uint16_t i = 0; i < 255; i++)
	{
		set_all(leds, CHSV(color.hue, color.sat, i));
		delay(delay_time);
	}
}

void fill_strip(CRGB * leds, uint16_t section_start, uint8_t up_or_down, uint16_t delay_time, CHSV color)
{
	if (UP) // Fill upwards
	{
		for (uint16_t i = section_start; i <= section_start + NUM_LEDS_PER_STRIP; i++)
		{
			leds[i] = color;
			FastLED.show();
			delay(delay_time);
		}
	}
	else // Fill downwards
	{
		for (uint16_t i = section_start + NUM_LEDS_PER_STRIP; i >= section_start; i--)
		{
			leds[i] = color;
			FastLED.show();
			delay(delay_time);
		}
	}
}

// Show functions
void blink_strip(CRGB * leds, uint16_t section_start,  uint16_t delay_time, CHSV color)
{
	set_strip(leds, section_start, color);
	delay(delay_time);
	set_strip(leds, section_start, CHSV(0, 0, 0));
	delay(delay_time);
}

void fade_color_upwards(CRGB * leds, uint16_t delay_time, CHSV color)
{
	fade_strip(leds, STRIP3, delay_time, color);
	fade_strip(leds, STRIP2, delay_time, color);
	fade_strip(leds, STRIP1, delay_time, color);
	fade_strip(leds, STRIP0, delay_time, color);
}

void fade_color_downwards(CRGB * leds, uint16_t delay_time, CHSV color)
{

	fade_strip(leds, STRIP0, delay_time, color);
	fade_strip(leds, STRIP1, delay_time, color);
	fade_strip(leds, STRIP2, delay_time, color);
	fade_strip(leds, STRIP3, delay_time, color);
}

void sinelon(CRGB * leds, CHSV color)
{
	unsigned long start_time = millis();
	while (millis() - start_time < 10000)
	{
		// a colored dot sweeping back and forth, with fading trails
		fadeToBlackBy(leds, NUM_LEDS-1, 20);
		int pos = beatsin16(13, 0, NUM_LEDS-1);
		leds[pos] += CHSV(color.hue, 255, 192);
		FastLED.delay(1000 / FRAMES_PER_SECOND);
	}
}

void juggle(CRGB * leds)
{
	unsigned long start_time = millis();
	while (millis() - start_time < 10000)
	{
		// eight colored dots, weaving in and out of sync with each other
		fadeToBlackBy(leds, NUM_LEDS-1, 20);
		byte dothue = 0;
		for (int i = 0; i < 8; i++) {
			leds[beatsin16(i + 7, 0, NUM_LEDS-1)] |= CHSV(dothue, 200, 255);
			dothue += 32;
		}
		FastLED.delay(1000 / FRAMES_PER_SECOND);
	}
}
