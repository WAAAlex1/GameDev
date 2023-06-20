#ifndef INITGAME_H
#define INITGAME_H

#define MODE_CHANGE gs_p->prevMode != gs_p->mode

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

	gamescore_t score;

	uint8_t LCDbuffer[512];
	uint8_t tickCounter;
	uint8_t spawnCounter;

	uint8_t mode;
	uint8_t prevMode;
	uint8_t gameInitialized;
	uint8_t playerNum;

} gameStruct_t;

uint8_t game_update();
void initProgram(gameStruct_t * gs_p);
void modeSelect(gameStruct_t * gs_p);
void initializeGame(gameStruct_t * gs_p, uint8_t numPlayers);
void clearGame(gameStruct_t * gs_p);
void updateGameFromInputs(gameStruct_t * gs_p, char input);
void drawGame(gameStruct_t * gs_p);
uint8_t modePicker(uint8_t mode, char input, gameStruct_t * gs_p);


uint8_t game_update();
void initializeStart(gameStruct * gs_p);
void initializeGame(gameStruct * gs_p, uint8_t numPlayers);
void clearGame(gameStruct * gs_p);
void updateGameFromInputs(gameStruct * gs_p);
void drawGame(gameStruct * gs_p);


#endif	// _INITGAME_
