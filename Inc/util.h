/*
 * util.h
 *
 *  Created on: 14. jun. 2023
 *      Author: georg
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "stdlib.h"
#include "stdio.h"

int getRandomInterval(int32_t min, int32_t max);
int abs(int32_t x);
int32_t getManDistance(int16_t x1, int16_t y1, int16_t x2, int16_t y2);


#endif /* UTIL_H_ */
