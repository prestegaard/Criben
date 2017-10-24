/*
 * msgeq7.h
 *
 * Created: 07.02.2017 11:22:34
 *  Author: medlem
 */ 


#ifndef MSGEQ7_H_
#define MSGEQ7_H_

#include <avr/io.h>

void msgeq7_init(void);
void msgeq7_read(uint16_t * filterVal,uint8_t highestFilter);

#endif /* MSGEQ7_H_ */