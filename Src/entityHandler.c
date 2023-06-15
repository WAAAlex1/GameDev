#include <stdint.h>
#include <stdio.h>
#include "entity.h"
#include "entityHandler.h"

// for each entity in our entityHandler array - move the entity and hide it if it's dead (isAlive())
void updateEntities(entityHandler_t * ptr){
	uint8_t i;

	for(i = 0; i < 128; i++){
		if(ptr->entityArray[i].setActive == 0){continue;}
		move(&(ptr->entityArray[i]));
		isAlive(&(ptr->entityArray[i]));
	}
}

// to initialize our entityhandler we fill it with entities
//
void init_entityHandler(entityHandler_t * ptr){
	uint8_t i;
	entity_t temp;
	initEntity(&temp, 0, 0, 0);
	for(i = 0; i < 128; i++)
		{
		ptr->entityArray[i] = temp;
		}
}

//Overwrites the first entity found in our entityArray with a new entity
//where setActive = 1 and spriteIndex can be set.
void pushEntity(entityHandler_t * ptr, uint8_t spriteIndex, uint8_t x, uint8_t y){
	uint8_t i;
	entity_t temp;
	initEntity(&temp, spriteIndex, x, y);
	for(i = 0; i < 128; i++){
		if(ptr->entityArray[i].setActive == 0){
			temp.entityIndex = i;
			toggleActive(&temp);
			ptr->entityArray[i] = temp;
			break;
		}
		else{ptr++;}
	}
}




