/*
 * bulletManager.c
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#include "entity.h"
#include "bullet.h"
#include "entityHandler.h"
#include "bulletManager.h"

void spawnBullet(bulletManager_t *bulletManager, entityHandler_t *entHand,bullet_t *bullet, uint8_t x, uint8_t y, uint8_t bulletType, uint8_t height)
{
	entity_t temp;
	pushEntity(entHand, 6,x,y);
	initBullet(bullet,&temp,bulletType,height);
}
