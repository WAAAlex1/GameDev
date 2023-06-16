#ifndef ENTITYHANDLER_H_
#define ENTITYHANDLER_H_

// INCLUDES

// DEFINES

#define ENTITY_ARR_LEN 128

typedef struct{
	entity_t entityArray[ENTITY_ARR_LEN];
} entityHandler_t;

void updateEntities(entityHandler_t * ptr);
void activateEntity(entityHandler_t * ptr1, uint8_t X_index, uint8_t Y_index);
void pushEntity(entityHandler_t * ptr, entity_t * temp, uint8_t spriteIndex, uint8_t x, uint8_t y);
void applyGravity(entityHandler_t * array);
void detectCollision();
void applyGravity(entityHandler_t * array);
void drawEntity(entity_t * ptr);
void clearEntity(entity_t * ptr);


#endif /* ENTITYHANDLER_H_ */
