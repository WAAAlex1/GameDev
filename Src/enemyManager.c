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

void initEnemyManager(enemyManager_t *enemyManager,enemy_t *enemArr)
{
	for(uint8_t i = 0; i < ENEMY_ARR_LENGTH; i++)
	{
		enemyManager->enemyArray[i] = &(enemArr[i]);
		enemyManager->enemyArray[i]->entity = (entity_t*)malloc(sizeof(entity_t));
		enemyManager->enemyArray[i]->entity->isActive = 0;
	}
}

void spawnEnemy(enemyManager_t *enemyManager,entity_t *entArr, uint8_t xPos, uint8_t yPos,uint8_t xVel, uint8_t yVel,uint8_t enemyType, uint8_t height, uint8_t fixedVel)
{
	for(uint8_t i = 1; i <= ENEMY_ARR_LENGTH; i++)
	{
		if(!(entArr[i].isActive))
		{
			initEntity(&(entArr[i]),2+enemyType,xPos,yPos,xVel,yVel,fixedVel,height);


			for(int j = 0; j < BULLET_ARR_LENGTH; j++)
			{
				if(!(enemyManager->enemyArray[j]->entity->isActive))
				{
					initEnemy(&(entArr[i]),enemyManager->enemyArray[j],enemyType);
					break;
				}
			}
			entArr[i].isActive = 1;

			break;
		}
	}

	//if no empty spot is found the new enemy is simply not spawned
}


void spawnRandom(enemyManager_t * enemMan, entity_t * entArr)
{
	spawnEnemy(enemMan,entArr,getRandomInterval(0,35),-2,0,1,getRandomInterval(0,4),getRandomInterval(0,3),0);
}








































