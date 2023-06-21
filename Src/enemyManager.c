/*
 * enemyManager.c
 *
 *  Created on: 19. jun. 2023
 *      Author: frede
 */

#include "enemy.h"
#include "entity.h"
#include <stdlib.h>
#include "enemyManager.h"
#include "bulletManager.h"

void initEnemyManager(enemyManager_t *enemyManager,enemy_t *enemArr)
{
	for(uint8_t i = 0; i < ENEMY_ARR_LENGTH; i++)
	{
		enemyManager->enemyArray[i] = &(enemArr[i]);
		enemyManager->enemyArray[i]->entity = (entity_t*)malloc(sizeof(entity_t));
		enemyManager->enemyArray[i]->entity->isActive = 0;
	}
}

void spawnEnemy(enemyManager_t *enemyManager,entityHandler_t *entHan, uint8_t xPos, int16_t yPos,int32_t xVel, int32_t yVel,uint8_t enemyType, uint8_t height, uint8_t fixedVel)
{
	for(uint8_t i = 1; i <= ENEMY_ARR_LENGTH; i++)
	{
		if(!(entHan->entityArray[i]->isActive))
		{
			initEntity(entHan->entityArray[i],2+enemyType,xPos,yPos,xVel,yVel,fixedVel,height);

			for(uint8_t j = 0; j < ENEMY_ARR_LENGTH; j++)
			{
				if(!(enemyManager->enemyArray[j]->entity->isActive))
				{
					initEnemy(entHan->entityArray[i],enemyManager->enemyArray[j],enemyType);
					break;
				}
			}
			entHan->entityArray[i]->isActive = 1;
			break;
		}
	}

	//if no empty spot is found the new enemy is simply not spawned
}


void spawnRandom(enemyManager_t * enemMan, entityHandler_t * entHan, uint8_t maxHeight)
{
	spawnEnemy(enemMan,entHan,getRandomInterval(0,70),-2,0,1 << 12,getRandomInterval(0,4),getRandomInterval(0, maxHeight+1),1);
}


void enemiesShoot(bulletManager_t *bulMan, entityHandler_t *entHan, enemyManager_t *enemMan)
{
	for(int i = 0; i < ENEMY_ARR_LENGTH;i++)
	{
		if(enemMan->enemyArray[i]->entity->isActive && enemMan->enemyArray[i]->type == 0) //only active spaceships
		{
			enemyShoot(bulMan,entHan,enemMan->enemyArray[i]);
		}
	}
}





































