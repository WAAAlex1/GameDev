#ifndef ENTITYHANDLER_H_
#define ENTITYHANDLER_H_

// INCLUDES

// DEFINES

typedef struct{
	entity_t entityArray[128];
} entityHandler_t;

void updateEntities(entityHandler_t * ptr);
void activateEntity(entityHandler_t * ptr1, uint8_t X_index, uint8_t Y_index);
void pushEntity(entityHandler_t * ptr, uint8_t spriteIndex);


#endif /* ENTITYHANDLER_H_ */
