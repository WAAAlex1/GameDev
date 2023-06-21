/*
 * bulletManager.c
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#include "enemyManager.h"
#include "entity.h"
#include "bullet.h"
#include "entityHandler.h"
#include <stdlib.h>
#include "scoreCalc.h"
#include "buzz.h"
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

void spawnBullet(bulletManager_t *bulletManager,entityHandler_t *entHan,int16_t xPos, int16_t yPos,int32_t xVel,int32_t yVel,uint8_t fixedVel,uint8_t bulletType, uint8_t height, uint8_t friendly)
{
	for(uint8_t i = BULLET_ARR_LENGTH; i < ENTITY_ARR_LEN; i++)
	{
		if(!(entHan->entityArray[i]->isActive))
		{
			initEntity(entHan->entityArray[i],6+bulletType,xPos,yPos,xVel,yVel,fixedVel,height);

			for(uint8_t j = 0; j < BULLET_ARR_LENGTH; j++)
			{
				if(!(bulletManager->bulletArray[j]->entity->isActive))
				{
					initBullet(bulletManager->bulletArray[j],entHan->entityArray[i],bulletType, friendly);
					break;
				}
			}
			entHan->entityArray[i]->isActive = 1;
			break;
		}
	}

	//if no empty spot is found the new bullet is simply not spawned
}

//bullets should collide with asteroids and enemy ships. We check if player collide with bullets in player.
//bullets should only collide if same height as the other object.
void checkBulletCollision(bulletManager_t *bulletManager, entityHandler_t *entityHandler, gamescore_t *score)
{
	uint8_t v;
	uint8_t w;
	for(w = 0; w < BULLET_ARR_LENGTH; w++)
	{
		if(bulletManager->bulletArray[w]->entity->isActive)
		{
			for(v = 1; v < ENEMY_ARR_LENGTH; v++) //only check enemies not player
			{
				if(entityHandler->entityArray[v]->isActive && entityHandler->entityArray[v]->spriteIndex <= 5)
				{
					if(detectEntityCollision(bulletManager->bulletArray[w]->entity, entityHandler->entityArray[v]))
					{
						if(bulletManager->bulletArray[w]->type == 0)
						{
							if(bulletManager->bulletArray[w]->entity->height >= entityHandler->entityArray[v]->height && bulletManager->bulletArray[w]->entity->height <= entityHandler->entityArray[v]->height + 2)
							{
								if(bulletManager->bulletArray[w]->friendly)
								{
									if(entityHandler->entityArray[v]->spriteIndex == 2) incrementScore(score, 2222);
									else incrementScore(score, 1111);
									setFreq(100);
								}
								destroyEntity(bulletManager->bulletArray[w]->entity);
								destroyEntity(entityHandler->entityArray[v]);
							}
						}
						else
						{
							destroyEntity(entityHandler->entityArray[v]);
						}

					}
				}
			}
		}
	}
}


