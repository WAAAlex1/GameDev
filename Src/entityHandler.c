#include <stdint.h>
#include <stdio.h>
#include "entity.h"
#include "entityHandler.h"

// to initialize our entityhandler we fill it with entities
void init_entityHandler(entityHandler_t * ptr){
	uint8_t i;
	entity_t temp;
	initEntity(&temp, 0, 0, 0,0,0);
	for(i = 0; i < ENTITY_ARR_LEN; i++)
		{
		ptr->entityArray[i] = temp;
		}
}

// for each entity in our entityHandler array - move the entity and hide it if it's dead
void updateEntities(entityHandler_t * ptr){
	uint8_t i;

	for(i = 0; i < 128; i++){
		if(ptr->entityArray[i].isActive == 0){continue;}
		move(&(ptr->entityArray[i]));
		isAlive(&(ptr->entityArray[i]));
	}
}

//Overwrites the first inactive entity found in our entityArray with a new entity
//where setActive = 1 and spriteIndex can be set.
void pushEntity(entityHandler_t * ptr, entity_t * temp, uint8_t spriteIndex, uint8_t xPos, uint8_t yPos,uint8_t xVel, uint8_t yVel){
	uint8_t i;
	initEntity(&temp, spriteIndex, xPos, yPos,xVel,yVel);
	for(i = 0; i < 128; i++){
		if(ptr->entityArray[i].isActive == 0){
			temp->entityIndex = i;
			ptr->entityArray[i] = *temp;
			temp = &(ptr->entityArray[i]);
			break;
		}
	}
}

void drawAllEntities(entityHandler_t * ptr){
	uint8_t i;
	for(i = 0; i < ENTITY_ARR_LEN; i++){
		drawEntity(ptr->entityArray[i]);
	}
}

void clearAllEntities(entityHandler_t * ptr){
	uint8_t i;
	for(i = 0; i < ENTITY_ARR_LEN; i++){
		clearEntity(ptr->entityArray[i]);
	}
}

//Collision between player & bullet
//Collision between player & enemy ships
//Collision between player & asteroids
//Collision between bullet & asteroids
//Collision between bullet & enemy ships
//Collision between mega bullet & enemy ships
//Collision between mega bullet & asteroids.


//Gravity between each bullet and each asteroid in range
void applyGravity(entityHandler * ptr){
	uint8_t i;
	uint8_t j;
	for(i = 0; i < ENTITY_ARR_LEN; i++){
		if(ptr->entityArray[i].spriteIndex == 6){
			for(j = 0; j < ENTITY_ARR_LEN; j++){
				if(ptr->entityArray[i].spriteIndex >= 3 && ptr->entityArray[i].spriteIndex <= 5){
					calculateGravity(entityArray[i], entityArray[j]);
				}
			}
		}
	}
}



