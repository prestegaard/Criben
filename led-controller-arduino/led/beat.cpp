/*
 * beat.cpp
 *
 * Created: 12/06/2015 17:44:06
 *  Author: Lua
 */ 


#include <avr/io.h>
#include "beat.h"
#include <util/delay.h>
#include "msgeq7_lauritz.h"
#include <stdio.h>

uint8_t isBeat(void){
	static uint8_t beat=0; //1 if beat, 0 if not beat
	static uint16_t indexBeat=0;
	static uint16_t beatVal=50;
	static uint16_t noBeatCount=0;
	static uint16_t offset=0;
	static uint16_t minVal=300;

	static uint16_t filterval[7]={0};
	msgeq7_read(filterval,N_FILTER);
	
	//find beat, iterate through output list
	//printf("low:  %d\t",filterval[0]);
	//printf("high: %d\n",filterval[1]);

	// beat should be zero when 
	if (beat==0){
		for (uint8_t i=0; i<N_FILTER;i++){
			if (filterval[i]>beatVal-offset){ // high value and not already beat
				beatVal=filterval[i];
				noBeatCount=0;
				beat=1;
				indexBeat=i;
				return 1;
			}
		}
		if(beatVal>minVal){
			beatVal--;
		}
	}
	
	else {//beat==1
		//4 is nice! changed to 5
		if ((filterval[indexBeat]*2.5<beatVal) && (noBeatCount >= 700)){ //if value on filter is X times lower than it was when the beat was detected, count as no beat.
			beat=0;
			noBeatCount=0;
			return 0;
		}
		
		else {
			noBeatCount++;
		}
		
		if (noBeatCount>=1000){
			for (uint8_t i=0; i<indexBeat;i++){ //check filters lower than beatindex
				if(filterval[i]>beatVal){
					beatVal=filterval[i];
					noBeatCount=0;
					beat=1;
					indexBeat=i;
					return 1;
				}
			}
		}
		if (noBeatCount>4096){ //no beat for very long time, increase indexbeat to so that next iteration will check all filters 
			beat=0;
		}
	}
	return 0;
}