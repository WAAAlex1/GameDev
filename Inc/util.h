/*
 * util.h
 *
 *  Created on: 14. jun. 2023
 *      Author: georg
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "stdint.h"

#define G 0x0001

int32_t getRandomInterval(int32_t min, int32_t max);
int32_t absolute(int32_t x);
int32_t getManDistance(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
int32_t mapInterval(int32_t minOld, int32_t maxOld,int32_t minNew, int32_t maxNew,int32_t value);
int32_t capInterval(int32_t value, int32_t min, int32_t max);

#endif /* UTIL_H_ */
