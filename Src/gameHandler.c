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

void initProgram(gameStruct_t * gs_p){
	uart_init(1024000);
	clrscr();
	gs_p->tickCounter = 0;
	gs_p->mode = 0;
	gs_p->gameInitialized = 0;
	initTimerStuff(); //Comment to debug
}

void modeSelect(gameStruct_t * gs_p){
	switch(gs_p->mode){
	case(0):
		//Functions for main menu


		break;
	case(1):
		//Functions for Help menu


		break;
	case(2):
		//Functions for game (clear, update, draw...)
		if(gs_p->gameInitialized == 0) initializeGame(&gs_p, gs_p->numPlayers);
		break;
	case(3):
		//Functions for Boss key
		//Pause timer
		//Draw screen
		//EXIT on ESC (setMode = 2)
		break;
	default:
		gs_p->mode = 0;
	}
}

void initializeGame(gameStruct_t * gs_p, uint8_t numPlayers){
	//INIT CONTROL VARIABLES
	gs_p->spawnCounter = 0;
	gs_p->gameInitialized= 1;

	//INIT TOP LEVEL STRUCTS
	init_entityHandler(&(gs_p->entityArray));
	initBulletManager(&(gs_p->bulletArray));
	initEnemyManager(&(gs_p->enemyArray));

	//ADD PLAYER - WITH SET NUMBER OF PLAYERS.
	pushEntity(&(gs_p->entHan),&(gs_p->playerEnt),0,40,23,0,0,0,0);
	initPlayer(&(gs_p->playerEnt), &(gs_p->player), numPlayers);

	//INIT LCD (ONLY IF 2 PLAYERS)
	if(gs_p->numPlayers == 2){
		initLCD();
		lcd_clear_all(gs_p->LCDbuffer,0x00);
		lcd_push_buffer(gs_p->LCDbuffer);
	}

	//INIT CONTROLLER (do anyways for random seed)
	initController();
}

void clearGame(gameStruct_t * gs_p){
	if(gs_p->numPlayers == 2) lcd_clear_all(gs_p->LCDbuffer,0x00);
	clearAllEntities(&(gs_p->entHan));
	clearPlayer(&(gs_p->player));
}

void updateGameFromInputs(gameStruct_t * gs_p){
	updatePlayerVel(&(gs_p->player), get_key_pressed());
	if(gs_p->mode == 2) updateCrosshair(&(gs_p->player),readJoystick());
	updateEntities(&(gs_p->entHan));
}

void drawGame(gameStruct_t * gs_p){
	//LCD
	if(gs_p->mode == 2){
		//con_draw_putty_to_lcd(&(gs_p->enemMan),&(gs_p->player),&(gs_p->LCDbuffer));
		lcd_push_buffer(gs_p->LCDbuffer);
	}
	//Putty
	drawAllEntities(&(gs_p->entHan));
	drawPlayer(&(gs_p->player));
}




