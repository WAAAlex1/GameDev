#include <stdint.h>
#include <stdio.h>
#include "entity.h"
#include "entityHandler.h"

// to initialize our entityhandler we fill it with entities
//
void init_entityHandler(entityHandler_t * ptr){
	uint8_t i;
	entity_t temp;
	initEntity(&temp, 0, 0, 0);
	for(i = 0; i < 128; i++){ptr->entityArray[i] = temp;}
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
void pushEntity(entityHandler_t * ptr, entity_t * temp, uint8_t spriteIndex, uint8_t x, uint8_t y){
	uint8_t i;
	initEntity(&temp, spriteIndex, x, y);
	for(i = 0; i < 128; i++){
		if(ptr->entityArray[i].isActive == 0){
			temp->entityIndex = i;
			ptr->entityArray[i] = *temp;
			break;
		}
	}
}




/*
void detectCollision(){


}


void applyGravity(entityHandler * array){
 	for()

}
*/




void drawEntity(entity_t * ptr){
	ui_draw_sprite(ptr->spriteIndex, 15, 0, ptr->pos.x, ptr->pos.y);
}

void clearEntity(entity_t * ptr){
	ui_clear_sprite(ptr->spriteIndex, 15, 0, ptr->pos.x, ptr->pos.y);
}


