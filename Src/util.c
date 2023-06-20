/*
 * util.c
 *
 *  Created on: 14. jun. 2023
 *      Author: georg
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "stdlib.h"
#include "stdio.h"
#include "entity.h"
#include "util.h"

/*
 * Remember to initialize the PRNG with srand(int) before using this
 *
 * Returns a number from min to max. min is inclusive. max is exclusive.
 */
int32_t getRandomInterval(int32_t min, int32_t max)
{
	int32_t ran = rand() >> 16;
	return ((ran * (max-min)) / (RAND_MAX >> 16)) + min;
}


int32_t absolute(int32_t x)
{
	return x >= 0 ? x : -x;
}

/*
 * returns the manhattan distance of the integers (unreliable distance)
 */
int32_t getManDistance(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
	return abs(x1-x2) + abs(y1-y2);
}

int32_t norm(int32_t x)
{
	return (x > 0 ? 1 : -1);
}

/*
 * maxOld cannot be equal to minOld !!!!!!!!!!!
 */
int32_t mapInterval(int32_t minOld, int32_t maxOld,int32_t minNew, int32_t maxNew,int32_t value)
{
	return (value-minOld) * (maxNew-minNew) / (maxOld-minOld) + minNew;
}

int32_t capInterval(int32_t value, int32_t min, int32_t max)
{
	return  value > max ? max : (value < min ? min : value);
}

void incrementCounter(uint8_t * ptr){
	(*ptr)++;
}

void resetCounter(uint8_t * ptr){
	*ptr = 0;
}
