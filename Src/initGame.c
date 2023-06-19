#include "initGame.h"


void initializeGame(gameStruct * gs_p, uint8_t numPlayers){
	gs_p->tickCounter = 0;
	gs_p->spawnCounter = 0;

	uint8_t spawnCounter;
	init_entityHandler(&(gs_p->entityArray));
	initBulletManager(&(gs_p->bulletArray));
	initEnemyManager(&(gs_p->enemyArray));

	pushEntity(&(gs_p->entHan),&(gs_p->playerEnt),0,40,23,0,0,0,0);
	initPlayer(&(gs_p->playerEnt), &(gs_p->player), numPlayers);
}
