#include "entity.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "entity.h"
#include "vec.h"
#include "enemyManager.h"
#include "entityHandler.h"
#include "bulletManager.h"

// to initialize our entityhandler we fill it with entities
void init_entityHandler(entityHandler_t * ptr, entity_t * entArr){
	uint8_t i;

	for(i = 0; i < ENTITY_ARR_LEN; i++)
	{
		ptr->entityArray[i] = &(entArr[i]);
		ptr->entityArray[i]->isActive = 0;
	}
}

// for each entity in our entityHandler array - move the entity
void updateEntities(entityHandler_t * ptr)
{
	uint8_t i;

	applyGravity(ptr);

	for(i = 0; i < ENTITY_ARR_LEN; i++)
	{
		if(ptr->entityArray[i]->isActive)
		{
			ptr->entityArray[i]->preX = getXint(&(ptr->entityArray[i]->pos));
			ptr->entityArray[i]->preY = getYint(&(ptr->entityArray[i]->pos));

			if(i == 0) //make sure player cant move outside the edges
			{
				if(withinBoundry(ptr->entityArray[0])) move(ptr->entityArray[0]);
				continue;
			}
			move(ptr->entityArray[i]);
			checkEntityPos(ptr->entityArray[i]);
		}
	}
}

void drawAllEntities(entityHandler_t * ptr){
	uint8_t i;
	for(i = 1; i < ENTITY_ARR_LEN; i++) //all except player
	{
		if(ptr->entityArray[i]->isActive && (ptr->entityArray[i]->preX != getXint(&(ptr->entityArray[i]->pos)) || ptr->entityArray[i]->preY != getYint(&(ptr->entityArray[i]->pos))))
		{
			drawEntity(ptr->entityArray[i],ptr->entityArray[i]->powerType);
		}
	}
}

void clearAllEntities(entityHandler_t * ptr){
	uint8_t i;
	for(i = 1; i < ENTITY_ARR_LEN; i++) //all except player
	{
		if(ptr->entityArray[i]->isActive && (ptr->entityArray[i]->preX != getXint(&(ptr->entityArray[i]->pos)) || ptr->entityArray[i]->preY != getYint(&(ptr->entityArray[i]->pos))))
		{
			clearEntity(ptr->entityArray[i]);
		}
	}
}

//Gravity between each bullet and each asteroid in range
void applyGravity(entityHandler_t * ptr)
{
	uint8_t i;
	uint8_t j;
	for(i = BULLET_ARR_LENGTH; i < ENTITY_ARR_LEN; i++)
	{
		if(ptr->entityArray[i]->isActive && ptr->entityArray[i]->spriteIndex == 6)
		{
			for(j = 1; j <= ENEMY_ARR_LENGTH; j++) //access the enemy part of entityarray
			{
				if(ptr->entityArray[j]->spriteIndex >= 3 && ptr->entityArray[j]->spriteIndex <= 5)
				{
					calculateGravity(ptr->entityArray[i], ptr->entityArray[j]);
				}
			}
		}
	}
}

uint8_t withinBoundry(entity_t *ptr)
{
	if(getXint(&(ptr->pos))+getXint(&(ptr->vel)) > 76 || getXint(&(ptr->pos))+getXint(&(ptr->vel)) < 1 || getYint(&(ptr->pos))+getYint(&(ptr->vel)) < 1 || getYint(&(ptr->pos))+getYint(&(ptr->vel)) > 42) return 0;
	else return 1;
}

