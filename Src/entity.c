#include "entity.h"

// API - generic functions for manipulating and controlling our entity_t struct.


//moves a given entity by its velocity. (both in fixed point so easy to add).
void move(entity_t * ptr){
	ptr->pos.x += ptr->vel.x;
	ptr->pos.y += ptr->vel.y;
}

//updates the velocity of a given struct.
void updateVel(entity_t * ptr, int8_t x, int8_t y){
	updateVectorInt(&(ptr->vel),x,y);
}

// MAINLY USED FOR INIT: --------------------------------------------------

//function to initialize the values of an entity struct and set its spriteindex.
void initEntity(entity_t * ptr, uint8_t spriteIndex, uint8_t xPos, uint8_t yPos,uint8_t xVel,uint8_t yVel, uint8_t fixedVel){
	setEntityPos(ptr,xPos,yPos);
	if(fixedVel)
	{
		setEntityVelFixed(ptr,xVel,yVel);
	}
	else
	{
		setEntityVel(ptr,xVel,yVel);
	}
	setSpriteIndex(ptr, spriteIndex);
	ptr->isActive = 0;
}

void setEntityVel(entity_t * ptr, int8_t x, int8_t y){
	setVectorInt(&(ptr->vel),x,y);
}

void setEntityVelFixed(entity_t *ptr, int32_t x, int32_t y)
{
	ptr->vel.x = x;
	ptr->vel.y = y;
}

void setEntityPos(entity_t * ptr, int8_t x, int8_t y){
	setVectorInt(&(ptr->pos),x,y);
}

//function for setting an entity's spriteindex to a passed value.
void setSpriteIndex(entity_t * ptr, uint8_t index){
	if(index >= 0 && index <= 7){ptr->spriteIndex = index;}
}

//-------------------------------------------------------------------------


//function to "destroy" an entity by setting it inactive.
void destroyEntity(entity_t * ptr){
	ptr->isActive = 0;
}

void calculateGravity(entity_t * bullet, entity_t * solidObj){
	int32_t x1 = bullet->pos.x;
	int32_t y1 = bullet->pos.y;
	int32_t x2 = solidObj->pos.x;
	int32_t y2 = solidObj->pos.y;

}




