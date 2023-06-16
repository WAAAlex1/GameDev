#include "entity.h"

// API - generic functions for manipulating and controlling our entity_t struct.


//moves a given entity by its velocity.
void move(entity_t * ptr){
	ptr->pos.x += ptr->vel.x;
	ptr->pos.y += ptr->vel.y;
}

//updates the velocity of a given struct.
void updateVel(entity_t * ptr, int8_t x, int8_t y){
	ptr->vel.x += x;
	ptr->vel.y += y;
}

// MAINLY USED FOR INIT: --------------------------------------------------

//function to initialize the values of an entity struct and set its spriteindex.
void initEntity(entity_t * ptr, uint8_t spriteIndex, uint8_t x, uint8_t y){
	setEntityPos(ptr,x,y);
	setEntityVel(ptr,0,0);
	setSpriteIndex(ptr, spriteIndex);
	ptr->isActive = 1;
}

void setEntityVel(entity_t * ptr, int8_t x, int8_t y){
	setVector(&(ptr->vel),x,y);
}

void setEntityPos(entity_t * ptr, int8_t x, int8_t y){
	setVector(&(ptr->pos),x,y);
}

//function for setting an entity's spriteindex to a passed value.
void setSpriteIndex(entity_t * ptr, uint8_t index){
	if(spriteIndex >= 0 && spriteIndex <= 7){ptr->spriteIndex = spriteIndex;}
}

//-------------------------------------------------------------------------


//function to "destroy" an entity by setting it inactive.
void destroyEntity(entity_t * ptr){
	ptr->isActive = 0;
}


