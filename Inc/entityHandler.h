#ifndef ENTITYHANDLER_H_
#define ENTITYHANDLER_H_

// INCLUDES

#include <stdint.h>
#include <stdio.h>
#include "entity.h"

// DEFINES

typedef struct{

	entity_t entityArray[128];

} entityHandler_t;

void updateEntities(entityHandler_t * ptr);
void activateEntity(entityHandler_t * ptr1, uint8_t X_index, uint8_t Y_index);
void spawnEnemies();



#endif /* ENTITYHANDLER_H_ */
