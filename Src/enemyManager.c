/*
 * enemyManager.c
 *
 *  Created on: 19. jun. 2023
 *      Author: frede
 */

#include "entity.h"
#include "enemyManager.h"

void initEnemyManager(enemyManager_t *enemyManager)
{
	entity_t tempEntity;
	enemy_t  tempEnemy;

	initEntity(&tempEntity,6,0,0,0,0,0,0);
	initEnemy(&tempEntity,&tempEnemy,0,0); //yes its intentional the array all points to the same enemy. Its just to set nonactive

	for(uint8_t i = 0; i < ENEMY_ARR_LENGTH; i++)
	{
		enemyManager->enemyArray[i] = &tempEnemy;
	}
}

void spawnEnemy(enemyManager_t *enemyManager, entityHandler_t *entHand, uint8_t xPos, uint8_t yPos,uint8_t xVel, uint8_t yVel,uint8_t enemyType, uint8_t height, uint8_t fixedVel)
{
	entity_t tempEntity;
	enemy_t  tempEnemy;

	pushEntity(entHand,&tempEntity,2+enemyType,xPos,yPos,xVel,yVel,fixedVel,height);
	initEnemy(&tempEntity,&tempEnemy,enemyType,height);
	tempEnemy.entity->isActive = 1;

	for(uint8_t i = 0; i < ENEMY_ARR_LENGTH; i++)
	{
		if(!(enemyManager->enemyArray[i]->entity->isActive))
		{
			*(enemyManager->enemyArray[i]) = tempEnemy;
			break;
		}
	}

	//if no empty spot is found the new enemy is simply not spawned :)
}


void spawnRandom(uint8_t spawnCounter, enemyManager_t * enemMan, entityHandler_t * entHan){
	if(spawnCounter == 20)
	{
		spawnEnemy(&enemMan,&entHan,getRandomInterval(0,70),0,0,1,getRandomInterval(0,3),getRandomInterval(0,3),0);
	}
}








































