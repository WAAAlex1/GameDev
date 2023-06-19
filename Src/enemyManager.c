/*
 * enemyManager.c
 *
 *  Created on: 19. jun. 2023
 *      Author: frede
 */

#include "entity.h"
#include "enemyManager.h"

void initEnemyManager(enemyManager_t *enemyManager, entityHandler_t *entHand)
{
	entity_t tempEntity;
	enemy_t  tempEnemy;

	for(uint8_t i = 0; i < ENEMY_ARR_LENGTH; i++)
	{
		pushEntity(entHand, &tempEntity, 6, 0, 0, 0, 0);
		initEnemy(&tempEntity,&tempEnemy,0,0);
		enemyManager->enemyArray[i] = tempEnemy;
	}
}

void spawnEnemy(enemyManager_t *enemyManager, entityHandler_t *entHand, uint8_t xPos, uint8_t yPos,uint8_t xVel, uint8_t yVel,uint8_t enemyType, uint8_t height)
{
	entity_t tempEntity;
	enemy_t  tempEnemy;

	initEntity(&tempEntity,6,xPos,yPos,xVel,yVel);
	initEnemy(&tempEntity,&tempEnemy,enemyType,height);
	tempEnemy.entity->isActive = 1;

	for(uint8_t i = 0; i < ENEMY_ARR_LENGTH; i++)
	{
		if(!(enemyManager->enemyArray[i].entity->isActive))
		{
			enemyManager->enemyArray[i] = tempEnemy;
			break;
		}
	}
}











































