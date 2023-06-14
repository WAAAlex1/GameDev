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


/*
 * returns the 18.14 fixed point format number for the distance
 */
int32_t getDistance(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{

}
