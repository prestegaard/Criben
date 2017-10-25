/*
Name:		LED_TEST.ino
Created:	9/4/2017 3:15:46 PM
Author:	Haagon
*/

#include <FastLED.h>
#include "leds.h"
#include "MSGEQ7.h"

CRGB leds[NUM_LEDS];

#define DATA_PIN 3
#define CHIPSET     WS2811

#define BRIGHTNESS  255  // reduce power consumption
#define LED_DITHER  255  // try 0 to disable flickering
#define CORRECTION  TypicalLEDStrip

// Filterchip setup
#define pinAnalogLeft A3 
#define pinAnalogRight A3
#define pinReset A1
#define pinStrobe A2
#define MSGEQ7_INTERVAL ReadsPerSecond(50)
#define MSGEQ7_SMOOTH true

CMSGEQ7<MSGEQ7_SMOOTH, pinReset, pinStrobe, pinAnalogLeft, pinAnalogRight> MSGEQ7;

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
  FastLED.setDither(LED_DITHER);
  
  red();
  FastLED.show();
  delay(2000);
  // This will set the IC ready for reading
  MSGEQ7.begin();

}

uint8_t gHue = 0;


int spectrumValue[7];
const int frames = 40;
int frame = 0;
int top_val = 0;
uint8_t strip_number = 0;
int bass[frames];
int snare[frames];
int hat[frames];
uint8_t val;
int count_color = 0;
int update_color = 5;
// the loop function runs over and over again until power down or reset
void loop() {
  // Analyze without delay
  bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

  // Led strip output
  if (newReading) {
    // visualize the average bass of both channels
    //uint8_t val = MSGEQ7.get(MSGEQ7_BASS);
    // Reduce noise
    //val = mapNoise(val);
    //if (val < 10){
    //  val = 5;
    //}
    
    spectrumValue[0] = MSGEQ7.get(0);
    spectrumValue[1] = MSGEQ7.get(1);
    spectrumValue[2] = MSGEQ7.get(2);
    spectrumValue[3] = MSGEQ7.get(3);
    spectrumValue[4] = MSGEQ7.get(4);
    spectrumValue[5] = MSGEQ7.get(5);
    spectrumValue[6] = MSGEQ7.get(6);
    
    int new_bass = spectrumValue[0] + spectrumValue[1];
    int new_snare = spectrumValue[3];
    int new_hat = spectrumValue[6] + spectrumValue[5];
  
    if ((new_snare/find_average(snare, frames)) > 1){
      //val = 10;
    }
    if ((new_hat/find_average(hat, frames)) > 1){
      //val = 50;
    }
    if ((new_bass/find_average(bass, frames)) > 1){
      val = new_bass;
      top_val = new_bass;
      count_color ++;
      strip_number ++;
      if(strip_number % 4 == 0)
      {
        strip_number = 0;
      }
        
      if(count_color % update_color == 0){
        gHue = gHue + random(0,255);
        update_color = random (1,10);
        count_color = 0;
      }
    }
    else if ((new_bass/find_average(bass, frames)) > 0.7){
      val = top_val--;
    }
    else {
      val = 30;
    }
    
    hat[frame] = new_hat;
    snare[frame] = new_snare;
    bass[frame] = new_bass;
    frame++;
    if (frame >= frames) frame=0;
  
    // Visualize leds to the beat
    CRGB color = CHSV(gHue, 255, 255);
    color.nscale8_video(val);
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
    
//    if(strip_number>0)
//    {
//      set_strip(leds, (strip_number*NUM_LEDS_PER_STRIP) -1, CHSV(gHue + 128, 255, 255));
//    }
//    else
//    {
//      set_strip(leds, STRIP0, CHSV(gHue + 128, 255, 255));
//    }
     
    // Update Leds
  }
	EVERY_N_MILLISECONDS(1000) { gHue++; } // slowly cycle the "base color" through the rainbow

}

int find_average(int ary[], int siz){
  double sum = 0;
  for (int i = 0; i < siz; i++){
    sum += ary[i];
  }
  return sum/siz;
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

