/*
 * enemyManager.h
 *
 *  Created on: 19. jun. 2023
 *      Author: frede
 */

#ifndef ENEMYMANAGER_H_
#define ENEMYMANAGER_H_

#define ENEMY_ARR_LENGTH 31

#include "entity.h"
#include "enemy.h"
#include <stdint.h>
#include "entityHandler.h"

typedef struct{
	enemy_t *enemyArray[ENEMY_ARR_LENGTH];
} enemyManager_t;

void initEnemyManager(enemyManager_t *enemyManager,enemy_t *enemArr);
void spawnEnemy(enemyManager_t *enemyManager,entityHandler_t *entHan, uint8_t xPos, int16_t yPos,int32_t xVel, int32_t yVel,uint8_t enemyType, uint8_t height, uint8_t fixedVel, uint8_t powerType);
void spawnRandom(enemyManager_t * enemMan, entityHandler_t * entHan, uint8_t maxHeight);
void enemiesShoot(bulletManager_t *bulMan, entityHandler_t *entHan, enemyManager_t *enemMan);


#endif /* ENEMYMANAGER_H_ */
