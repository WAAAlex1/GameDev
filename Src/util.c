/*
 * util.c
 *
 *  Created on: 14. jun. 2023
 *      Author: georg
 */

#include "util.h"

/*
 * Remember to initialize the PRNG with srand(int) before using this
 */
int getRandomInterval(int32_t min, int32_t max)
{
	return rand() * (max-min) / RAND_MAX + min;
}

int abs(int32_t x)
{
	return x >= 0 ? x : -x;
}


/*
 * returns the manhattan distance of the integers (unreliable distance)
 */
int32_t getManDistance(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	return abs(x1-x2) + abs(y1-y2);
}
