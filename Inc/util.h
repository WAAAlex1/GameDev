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
int32_t getManDistance(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
int32_t mapInterval(int32_t min1, int32_t max1,int32_t min2, int32_t max2,int32_t value);


#endif /* UTIL_H_ */
