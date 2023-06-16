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

void setEntityVel(entity_t * ptr, int8_t x, int8_t y){
	ptr->vel.x = x;
	ptr->vel.y = y;
}
void setEntityPos(entity_t * ptr, int8_t x, int8_t y){
	ptr->pos.x = x;
	ptr->pos.y = y;
}

//function to deal damage to an entity
//can also be used to "heal" an entity
void damageEntity(entity_t * ptr, int8_t x){
	ptr->hp -= x;
	ptr->hp = ptr->hp > 0 ? ptr->hp : 0;
	ptr->hp = ptr->hp > 3 ? 3 : ptr->hp;
}

//function to initialize the values of an entity struct and set its spriteindex.
void initEntity(entity_t * ptr, uint8_t spriteIndex, uint8_t x, uint8_t y){
	setEntityPos(ptr,x,y);
	setEntityVel(ptr,0,0);
	ptr->isActive = 1;

	if(spriteIndex >= 0 && spriteIndex <= 7){ptr->spriteIndex = spriteIndex;}
}

void isAlive(entity_t * ptr){
	if(ptr->hp < 1 && ptr->isActive) toggleActive(ptr);
}

//function to "destroy" an entity by setting it inactive.
void destroyEntity(entity_t * ptr){
	ptr->isActive = 0;
}

void setSpriteIndex(entity_t * ptr, uint8_t index){
	if(ptr->isActive >= 0 && ptr->isActive <= 7){ptr->spriteIndex = index;}
}
