#ifndef ENTITYHANDLER_H_
#define ENTITYHANDLER_H_

// INCLUDES
#include "enemy.h"
#include "entity.h"

// DEFINES

#define ENTITY_ARR_LEN 128

typedef struct{
	entity_t *entityArray[ENTITY_ARR_LEN];
} entityHandler_t;

void init_entityHandler(entityHandler_t * ptr, entity_t * entArr);
void updateEntities(entityHandler_t * ptr);
void pushEntity(entityHandler_t * ptr, entity_t * temp, uint8_t spriteIndex, uint8_t xPos, uint8_t yPos,uint8_t xVel, uint8_t yVel,uint8_t fixedVel,uint8_t height);
void applyGravity(entityHandler_t * array);
void drawAllEntities(entityHandler_t * ptr);
void clearAllEntities(entityHandler_t * ptr);


#endif /* ENTITYHANDLER_H_ */
