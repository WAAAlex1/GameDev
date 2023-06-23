#ifndef BULLETMANAGER_H_
#define BULLETMANAGER_H_

#define BULLET_ARR_LENGTH 16

#include "entityHandler.h"
#include "entity.h"
#include "bullet.h"
#include "scoreCalc.h"
#include <stdint.h>

typedef struct{
	bullet_t * bulletArray[BULLET_ARR_LENGTH];
} bulletManager_t;

void spawnBullet(bulletManager_t *bulletManager,entityHandler_t *entHan,int16_t xPos, int16_t yPos,int32_t xVel,int32_t yVel,uint8_t fixedVel,uint8_t bulletType, uint8_t height, uint8_t friendly);
void initBulletManager(bulletManager_t *bulletManager, bullet_t *bulArr);
void checkBulletCollision(bulletManager_t *bulletManager, entityHandler_t *entityHandler, gamescore_t *score,uint8_t *playerPowerUp);

#endif /* BULLETMANAGER_H_ */
