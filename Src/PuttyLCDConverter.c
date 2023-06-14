/*
 * PuttyLCDConverter.c
 *
 *  Created on: 14. jun. 2023
 *      Author: georg
 */


#include "PuttyLCDConverter.h"
#include "util.h"

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

/*
 * Returns an int in the interval [-3;2] based on distanceX from ship:
 * dist = ]0;8] returns 2
 * dist = ]8;16] returns 1
 * dist = ]16;24] returns 0
 * dist = ]24;32] returns -1
 * dist = ]32;40] returns -2
 * dist > 40 returns -3
 *
 * Add this with entity size to determine sprite-size to be drawn on the LCD
 */
int8_t con_getDistanceX(uint8_t playerX, uint8_t entX)
{
	switch((abs(playerX - entX)-1) / 8)
	{
		case 0:
			return 2;
		case 1:
			return 1;
		case 2:
			return 0;
		case 3:
			return -1;
		case 4:
			return -2;
		default:
			return -3;
	}
}

/*
 * Returns 1 if the entity is viewable inside the coneview
 * (also returns 1 if the entities position is outside the cone but part of its sprite could be inside)
 *
 * Returns 0 if the entity is NOT viewable inside the coneview
 *
 * Parameters:
 * 		gunside = 1 for left and = -1 for right
 */
uint8_t con_inCone(uint8_t playerX, uint8_t playerY, uint8_t entX, uint8_t entY, int8_t gunside)
{
	if(playerX - entX <= CONE_VIEW_LENGTH * gunside && absolute(playerY - entY) <= ((CONE_VIEW_WIDTH * absolute(playerX - entX)) / (2*CONE_VIEW_LENGTH)) + 2)
	{
		return 1;
	}
	else{return 0;}
}


/*
 * returns the slice for the entity to be drawn on
 *
 * can return slices outside of [0:128] so that entities on their way into the cone view can be drawn smoothly moving in
 *
 *Should probably only return the interval [-39;128]
 *
 * Parameters:
 * 		gunside = 1 for left and = -1 for right
 */
int16_t con_posToSlice(uint16_t playerX, uint16_t playerY, uint16_t entX, uint16_t entY)
{
	return (((((CONE_VIEW_WIDTH * absolute(playerX - entX)) / (2*CONE_VIEW_LENGTH)) + 2) * 2) * absolute(playerY - entY)) / 128;
	return mapInterval(0,((CONE_VIEW_WIDTH * absolute(playerX - entX)) / (2*CONE_VIEW_LENGTH)) * 2,0,128); //minOld should be something else here to allow negative slices
	/*
	 * continue here
	 *
	 * return statement nummer 2 var det jeg var igang med,
	 * men problemet er at value for den map skal være [0;32] for entity der bevæger sig fra toppen til bunden af keglen
	 */
}



