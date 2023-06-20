#ifndef INITGAME_H
#define INITGAME_H

#include "stdint.h"
#include "entityHandler.h"
#include "bulletManager.h"
#include "enemyManager.h"
#include "player.h"
#include "LCD.h"
#include "stm32f30x.h"
#include "stopwatch.h"

#define ENTITY_ARR_LEN 128
#define BULLET_ARR_LENGTH 64
#define ENEMY_ARR_LENGTH 63

typedef struct{
	entityHandler_t entHan;
	entity_t entityArray[ENTITY_ARR_LEN];

	bulletManager_t bulMan;
	bullet_t bulletArray[BULLET_ARR_LENGTH];

	enemyManager_t enemMan;
	enemy_t enemyArray[ENEMY_ARR_LENGTH];

	player_t player;

	uint8_t LCDbuffer[512];
	uint8_t tickCounter;
	uint8_t spawnCounter;
	uint8_t numPlayers;
	uint8_t mode;

} gameStruct;

uint8_t game_update();
void initializeStart(gameStruct * gs_p);
void initializeGame(gameStruct * gs_p, uint8_t numPlayers);
void clearGame(gameStruct * gs_p);
void updateGameFromInputs(gameStruct * gs_p);
void drawGame(gameStruct * gs_p);


#endif	// _INITGAME_
