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

void initBulletManager(bulletManager_t *bulletManager)
{
	entity_t tempEnt; //just used to get the right size
	bullet_t tempBul;

	initEntity(&tempEnt,6,0,0,0,0,0,0);

	for(int i = 0; i < BULLET_ARR_LENGTH; i++)
	{
		initBullet(&tempBul,&tempEnt,0,0); //yes its intentional they all point to the same as its just a placeholder
		bulletManager->bulletArray[i] = tempBul;
	}
}

void spawnBullet(bulletManager_t *bulletManager, entityHandler_t *entHand, uint8_t xPos, uint8_t yPos,uint8_t xVel,uint8_t yVel,uint8_t fixedVel,uint8_t bulletType, uint8_t height)
{
	bullet_t tempBul;
	entity_t tempEnt;

	pushEntity(entHand,&tempEnt,6+bulletType,xPos,yPos,xVel,yVel,fixedVel,height);
	initBullet(&tempBul,&tempEnt,bulletType,height);
	tempBul.entity->isActive = 1;

	for(int i = 0; i < BULLET_ARR_LENGTH; i++)
	{
		if(!(bulletManager->bulletArray[i].entity->isActive))
		{
			bulletManager->bulletArray[i] = tempBul;
			break;
		}
	}

	//if no empty spot is found the new bullet is simply not spawned :)
}

//bullets should collide with asteroids and enemy ships. We check if player collide with bullets in player.
//bullets should only collide if same height as the other object.
void checkBulletCollision(bulletManager_t *bulletManager, entityHandler_t *entityHandler){
	uint8_t v;
	uint8_t w;
	for(w = 0; w < BULLET_ARR_LENGTH; w++)
	{
		for(v = 0; v < ENTITY_ARR_LEN; v++)
		{
			if(entityHandler->entityArray[v]->spriteIndex >= 2 && entityHandler->entityArray[v]->spriteIndex <= 5)
			{
				if(detectEntityCollision(bulletManager->bulletArray[w], entityHandler->entityArray[v]))
				{
					if(bulletManager->bulletArray[w]->entity->height == entityHandler->entityArray[v]->height)
					{
						bulletManager->bulletArray[w]->entity->isActive = bulletManager->bulletArray[w]->type == 1 ? 1 : 0;
						entityHandler->entityArray[v]->isActive = 0;
					}
				}
			}
		}
	}
}


