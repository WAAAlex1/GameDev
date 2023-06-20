#ifndef INITGAME_H
#define INITGAME_H

typedef struct{
	entityHandler_t entHan;
	entity_t entityArray[ENTITY_ARR_LEN];

	bulletManager_t bulMan;
	bullet_t bulletArray[BULLET_ARR_LENGTH];

	enemyManager_t enemMan;
	enemy_t enemyArray[ENEMY_ARR_LENGTH];

	player_t player;
	entity_t playerEnt;

	gamescore_t score;

	uint8_t LCDbuffer[512];
	uint8_t tickCounter;
	uint8_t spawnCounter;

	uint8_t mode;
	uint8_t prevMode;
	uint8_t gameInitialized;

} gameStruct_t;

uint8_t game_update();
void initProgram(gameStruct * gs_p);
void initializeGame(gameStruct * gs_p, uint8_t numPlayers);
void clearGame(gameStruct * gs_p);
void updateGameFromInputs(gameStruct * gs_p, char input);
void drawGame(gameStruct * gs_p);


#endif	// _INITGAME_
