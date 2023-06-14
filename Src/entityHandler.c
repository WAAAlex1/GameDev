#include "entityHandler.h"

// for each entity in our entityHandler array - move the entity and hide it if it's dead (isAlive())
void updateEntities(entityHandler_t * ptr){
	uint8_t i;

	for(i = 0; i < 128; i++)
	{
		if(!ptr->entityArray[i]) continue;
		move(ptr->entityArray[i]);
		isAlive(ptr->entityArray[i]);
	}
}

void init_entityHandler(entityHandler_t * ptr){
	for(i = 0; i < 128; i++)
		{
		ptr->entityArray[i] = NULL;
		}
}

void pushEntity(entityHandler_t * ptr, uint8_t spriteIndex){
	uint8_t i;
	entity_t temp;
	initEntity(&temp, spriteIndex);
	for(i = 0; i < 128; i++){
		if(!ptr->entityHandler[i]){
			temp.entityIndex = i;
			*ptr = temp;
			break;
		}
		else{ptr++;}
	}
}




void spawnEnemies(){

}

