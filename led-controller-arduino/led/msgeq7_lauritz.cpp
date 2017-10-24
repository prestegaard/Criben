/*
 * msgeq7.cpp
 *
 * Created: 07.02.2017 11:22:23
 *  Author: medlem
 */ 

 #include <avr/io.h>
 #include <util/delay.h>
 #include "io.h"
 #include <stdio.h>
#include "Arduino.h"

void msgeq7_init(void){
	//Strobe and reset as outputs
	pinMode(MSGEQ7_RESET, OUTPUT);
	pinMode(MSGEQ7_STROBE, OUTPUT);
	//Reset chip
	digitalWrite(MSGEQ7_RESET, HIGH);
	_delay_ms(1);

	digitalWrite(MSGEQ7_RESET, LOW);
	//PORTD &= ~(1 << MSGEQ7_STROBE);
	digitalWrite(MSGEQ7_STROBE, HIGH);
}

void msgeq7_read(uint16_t * filterVal,uint8_t highestFilter){
	digitalWrite(MSGEQ7_RESET, HIGH);
	_delay_us(10);
	digitalWrite(MSGEQ7_RESET, LOW);
	//PORTD |= (1 << MSGEQ7_STROBE);
	_delay_us(75);
	for (uint8_t i=0;i<highestFilter;i++){
		digitalWrite(MSGEQ7_STROBE, LOW);
		_delay_us(40);
		filterVal[i]=analogRead(MSGEQ7_OUT);
		digitalWrite(MSGEQ7_STROBE, HIGH);
		_delay_us(40);
	}
}
