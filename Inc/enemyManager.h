/*
 * enemyManager.h
 *
 *  Created on: 19. jun. 2023
 *      Author: frede
 */

#ifndef ENEMYMANAGER_H_
#define ENEMYMANAGER_H_

#define ENEMY_ARR_LENGTH 63

#include "enemy.h"
#include <stdint.h>
#include "entityHandler.h"

typedef struct{
	enemy_t *enemyArray[ENEMY_ARR_LENGTH];
} enemyManager_t;

void initEnemyManager(enemyManager_t *enemyManager);
void spawnEnemy(enemyManager_t *enemyManager, entityHandler_t *entHand, uint8_t xPos, uint8_t yPos,uint8_t xVel, uint8_t yVel,uint8_t enemyType, uint8_t height, uint8_t fixedVel);
void spawnRandom(uint8_t spawnCounter, enemyManager_t * enemMan, entityHandler_t * entHan);


#endif /* ENEMYMANAGER_H_ */
