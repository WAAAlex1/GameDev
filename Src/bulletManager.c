/*
 * bulletManager.c
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#include "entity.h"
#include "bullet.h"
#include "entityHandler.h"
#include <stdlib.h>
#include "bulletManager.h"

void initBulletManager(bulletManager_t *bulletManager, bullet_t *bulArr)
{
	for(int i = 0; i < BULLET_ARR_LENGTH; i++)
	{
		bulletManager->bulletArray[i] = &(bulArr[i]);
		bulletManager->bulletArray[i]->entity = (entity_t*)malloc(sizeof(entity_t));
		bulletManager->bulletArray[i]->entity->isActive = 0;
	}

}

void spawnBullet(bulletManager_t *bulletManager,entity_t *entArr,uint8_t xPos, uint8_t yPos,int32_t xVel,int32_t yVel,uint8_t fixedVel,uint8_t bulletType, uint8_t height)
{
	for(int i = BULLET_ARR_LENGTH; i < ENTITY_ARR_LEN; i++)
	{
		if(!(entArr[i].isActive))
		{
			initEntity(&(entArr[i]),6+bulletType,xPos,yPos,xVel,yVel,fixedVel,height);

			for(int j = 0; j < BULLET_ARR_LENGTH; j++)
			{
				if(!(bulletManager->bulletArray[j]->entity->isActive))
				{
					initBullet(bulletManager->bulletArray[j],&(entArr[i]),bulletType);
					break;
				}
			}
			entArr[i].isActive = 1;
			break;
		}
	}

	//if no empty spot is found the new bullet is simply not spawned
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


