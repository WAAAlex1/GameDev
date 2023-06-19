/*
 * bulletManager.h
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#ifndef BULLETMANAGER_H_
#define BULLETMANAGER_H_

#define BULLET_ARR_LENGTH 64

#include "bullet.h"
#include <stdint.h>
#include "entityHandler.h"

typedef struct{
	bullet_t *bulletArray[BULLET_ARR_LENGTH];
} bulletManager_t;

void spawnBullet(bulletManager_t *bulletManager, entityHandler_t *entHand, uint8_t xPos, uint8_t yPos,uint8_t xVel,uint8_t yVel,uint8_t fixedVel,uint8_t bulletType, uint8_t height);
void initBulletManager(bulletManager_t *bulletManager,bullet_t *placeholder);


#endif /* BULLETMANAGER_H_ */
