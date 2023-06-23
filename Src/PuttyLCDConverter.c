/*
 * PuttyLCDConverter.c
 *
 *  Created on: 14. jun. 2023
 *      Author: georg
 */

#include "stdio.h"
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "util.h"
#include "LCD.h"
#include "vec.h"
#include "PuTTYSprites.h"
#include "entity.h"
#include "PuttyLCDConverter.h"

#define CONE_VIEW_WIDTH 32
#define CONE_VIEW_LENGTH 40

/*
 * Returns the fixed point 18.14 y coordinate for the unitvector in the direction given by the LCD slice
 *
 * for left gunside = 1;
 * for right gunside = -1;
 */
int32_t con_getVecY(uint8_t slice, int8_t gunside)
{
	return (-gunside)*(((((slice+1) >> 2) - 16) << 14) / CONE_VIEW_LENGTH); //rightshift by 2 to divide by 4
}

/*
 * Returns the fixed point 18.14 x coordinate for the unitvector in the given gunner direction
 *
 * for left gunside = 1;
 * for right gunside = -1;
 */
int32_t con_getVecX(int8_t gunside)
{
	return (-gunside + 0x80000000) << 14; //plus with 0x80000000 to convert to a 32bit int for fixed point. Probably not needed
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
	switch((absolute(playerX - entX)-1) >> 3) //divide by 8
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
	if((gunside > 0 ? playerX > entX : entX > playerX) && absolute(playerX - entX) <= CONE_VIEW_LENGTH && absolute(playerY - entY) <= ((CONE_VIEW_WIDTH * absolute(playerX - entX)) / (2*CONE_VIEW_LENGTH)) + 2) //+2 to allow entities just outside to be drawn
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
 * Parameters:
 * 		gunside = 1 for left and = -1 for right
 */
int16_t con_posToSlice(uint8_t playerX, uint8_t playerY, uint8_t entX, uint8_t entY, int8_t gunside)
{
	int16_t temp = ((CONE_VIEW_WIDTH * (absolute(playerX - entX))) / (2*CONE_VIEW_LENGTH));
	int16_t coneY =  (temp == 0 ? 1 : temp); //to avoid div by zero

	//padding on the coneY value allows enemies to be drawn on the edge of the LCD
	return mapInterval(-coneY-2,coneY+2,(gunside < 0 ? -(256/coneY) : (128)+(256/coneY)),(gunside < 0 ? (128)+(256/coneY) : -(256/coneY)),(entY-playerY));
	/*-2 on minOld to allow ships slightly outside to be drawn smoothly in
	 * same reason for -256/coneY and the same for the max
	*/
}


/*
 * Translates an enemy from putty space to LCD space. The enemy is drawn on the LCD if its inside the defined cone
 */
void con_draw_putty_to_lcd(enemyManager_t *enemMan, player_t *player,uint8_t * LCDbuffer)
{
	for(int i = 0; i < ENEMY_ARR_LENGTH; i++)
	{
		if(enemMan->enemyArray[i]->entity->isActive)
		{
			if(con_inCone(offsetBulletCoordXCone(player),offsetBulletCoordY(player),centeredXPOS(enemMan->enemyArray[i]->entity) >> 14,getYint(&(enemMan->enemyArray[i]->entity->pos))+2,player->gunSide))
			{
				//Perhaps this should be split into more lines
				lcd_draw_sprite(LCDbuffer,con_posToSlice(offsetBulletCoordXCone(player),offsetBulletCoordY(player),centeredXPOS(enemMan->enemyArray[i]->entity) >> 14,getYint(&(enemMan->enemyArray[i]->entity->pos))+2,player->gunSide),enemMan->enemyArray[i]->entity->height,(enemMan->enemyArray[i]->type ? enemMan->enemyArray[i]->type : 10)+1+con_getDistanceX(offsetBulletCoordXCone(player),centeredXPOS(enemMan->enemyArray[i]->entity) >> 14),player->gunSide == 1 ? 1 : 0);
			}
		}
	}
}

