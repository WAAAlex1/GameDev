/*
 * PuttyLCDConverter.c
 *
 *  Created on: 14. jun. 2023
 *      Author: georg
 */


#include "PuttyLCDConverter.h"
#define CONE_VIEW_WIDTH 32
#define CONE_VIEW_LENGTH 40
#define CONE_VIEW_ANGLE 44

/*
 * Returns the fixed point 18.14 y coordinate for the unitvector in the direction given by the LCD slice
 */
int32_t con_getVecY(uint8_t slice)
{
	//a bug might occur here if the (slice/4 - 16) is seen as 1 byte long instead of 4 bytes long.
	return (((slice / 4) - 16) << 14) / CONE_VIEW_LENGTH;
}

/*
 * Returns the fixed point 18.14 x coordinate for the unitvector in the given gunner direction
 *
 * for left gunner direction set dir = -1;
 * for right gunnner direction set dir = 1;
 */
int32_t con_getVecX(int8_t dir)
{
	return ((CONE_VIEW_LENGTH * dir) << 14) / CONE_VIEW_LENGTH;
}

int8_t con_get


/*
 * returns the slice for the entity to be drawn on
 */
int16_t con_posToSlice(uint8_t playerX, uint8_t playerY, uint8_t entX, uint8_t entY)
{

}



