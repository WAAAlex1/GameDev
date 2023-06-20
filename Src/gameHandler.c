#include "PuttyLCDConverter.h"
#include "gameHandler.h"


uint8_t game_update()
{
	if(LCD_Flag == 1)
	{
		LCD_Flag = 0;
		return 1;
	}

	return 0;
}

void initializeStart(gameStruct * gs_p){
	gs_p->tickCounter = 0;
	initTimerStuff(); //Comment to debug
}

void initializeGame(gameStruct * gs_p, uint8_t numPlayers){
	//INIT CONTROL VARIABLES
	gs_p->spawnCounter = 0;
	gs_p->numPlayers = numPlayers;

	//INIT TOP LEVEL STRUCTS
	init_entityHandler(&(gs_p->entHan),gs_p->entityArray);
	initBulletManager(&(gs_p->bulMan),gs_p->bulletArray);
	initEnemyManager(&(gs_p->enemMan),gs_p->enemyArray);

	//ADD PLAYER - WITH SET NUMBER OF PLAYERS.
	initEntity(&(gs_p->entityArray[0]),0,40,23,0,0,0,0);
	gs_p->entityArray[0].isActive = 1;
	initPlayer(&(gs_p->entityArray[0]), &(gs_p->player), gs_p->numPlayers);

	//INIT LCD (ONLY IF 2 PLAYERS)
	if(gs_p->numPlayers == 2){
		initLCD();
		lcd_clear_all(gs_p->LCDbuffer,0x00);
		lcd_push_buffer(gs_p->LCDbuffer);
	}

	//INIT CONTROLLER
	initController();
}

void clearGame(gameStruct * gs_p){
	if(gs_p->numPlayers == 2) lcd_clear_all(gs_p->LCDbuffer,0x00);
	clearAllEntities(&(gs_p->entHan));
	clearPlayer(&(gs_p->player));
}

void updateGameFromInputs(gameStruct * gs_p){
	updatePlayerVel(&(gs_p->player), get_key_pressed());
	if(gs_p->numPlayers == 2) updateCrosshair(&(gs_p->player),readJoystick());
	updateEntities(&(gs_p->entHan));
}

void drawGame(gameStruct * gs_p){
	//LCD
	if(gs_p->numPlayers == 2){
		con_draw_putty_to_lcd(&(gs_p->enemMan),&(gs_p->player),gs_p->LCDbuffer);
		lcd_push_buffer(gs_p->LCDbuffer);
	}
	//Putty
	drawAllEntities(&(gs_p->entHan));
	drawPlayer(&(gs_p->player));
}




