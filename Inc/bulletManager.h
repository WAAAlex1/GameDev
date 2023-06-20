/*
 * bulletManager.h
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#ifndef BULLETMANAGER_H_
#define BULLETMANAGER_H_

#define BULLET_ARR_LENGTH 64

#include "entity.h"
#include "bullet.h"
#include <stdint.h>

typedef struct{
	bullet_t *bulletArray[BULLET_ARR_LENGTH];
} bulletManager_t;

void spawnBullet(bulletManager_t *bulletManager,entity_t *entArr,uint8_t xPos, uint8_t yPos,int32_t xVel,int32_t yVel,uint8_t fixedVel,uint8_t bulletType, uint8_t height);
void initBulletManager(bulletManager_t *bulletManager, bullet_t *bulArr);


#endif /* BULLETMANAGER_H_ */
