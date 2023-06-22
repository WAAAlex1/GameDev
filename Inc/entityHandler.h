#ifndef ENTITYHANDLER_H_
#define ENTITYHANDLER_H_

// INCLUDES
#include "entity.h"

// DEFINES

#define ENTITY_ARR_LEN 32

typedef struct{
	entity_t *entityArray[ENTITY_ARR_LEN];
} entityHandler_t;

void init_entityHandler(entityHandler_t * ptr, entity_t * entArr);
void updateEntities(entityHandler_t * ptr);
void applyGravity(entityHandler_t * array);
void drawAllEntities(entityHandler_t * ptr);
void clearAllEntities(entityHandler_t * ptr);
uint8_t withinBoundry(entity_t *ptr);

#endif /* ENTITYHANDLER_H_ */
