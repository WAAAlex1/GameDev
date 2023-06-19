#ifndef INITGAME_H
#define INITGAME_H

#include "stdint.h"
#include "entityHandler.h"
#include "bulletManager.h"
#include "enemyManager.h"

typedef struct{
	entityHandler_t entHan;
	entity_t entityArray[ENTITY_ARR_LEN];

	bulletManager_t bulMan;
	bullet_t bulletArray[BULLET_ARR_LENGTH];

	enemyManager_t enemMan;
	enemy_t enemyArray[ENEMY_ARR_LENGTH];

	player_t player;
	entity_t playerEnt;

	uint8_t LCDbuffer[512];
	uint8_t tickCounter;
	uint8_t spawnCounter;

} gameStruct;

#endif	// VEC_H
