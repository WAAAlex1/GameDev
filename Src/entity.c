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

//function to deal damage to an entity
//can also be used to "heal" an entity
void damage(entity_t * ptr, int8_t x){
	ptr->hp -= x;
	ptr->hp = ptr->hp > 0 ? ptr->hp : 0;
	ptr->hp = ptr->hp > 3 ? 3 : ptr->hp;
}

//function to initialize the values of an entity struct and set its spriteindex.
void initEntity(entity_t * ptr, uint8_t spriteIndex){
	ptr->pos.x = 0;
	ptr->pos.y = 0;
	ptr->vel.x = 0;
	ptr->vel.y = 0;
	ptr->setActive = 0;
	if(spriteIndex >= 0 && spriteIndex <= 8){ptr->spriteIndex = spriteIndex;}
}

//function to activate or deactivate an entity
void toggleActive(entity_t * ptr){
	ptr->setActive = ptr->setActive = 0 ? 1 : 0;
}

