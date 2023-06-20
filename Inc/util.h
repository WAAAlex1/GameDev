/*
 * util.h
 *
 *  Created on: 14. jun. 2023
 *      Author: georg
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "stdint.h"

int32_t getRandomInterval(int32_t min, int32_t max);
int32_t absolute(int32_t x);
int32_t getManDistance(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
int32_t mapInterval(int32_t minOld, int32_t maxOld,int32_t minNew, int32_t maxNew,int32_t value);
int32_t capInterval(int32_t value, int32_t min, int32_t max);
void incrementCounter(uint8_t * ptr, uint8_t count);
void resetCounter(uint8_t * ptr);
int32_t norm(int32_t x);


#endif /* UTIL_H_ */
