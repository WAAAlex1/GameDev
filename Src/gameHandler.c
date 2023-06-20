#include "stdint.h"
#include "entityHandler.h"
#include "bulletManager.h"
#include "enemyManager.h"
#include "player.h"
#include "LCD.h"
#include "stm32f30x.h"
#include "stopwatch.h"
#include "scoreCalc.h"
#include "menus.h"
#include "menusAPI.h"
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

void initProgram(gameStruct * gs_p){
	uart_init(1024000);
	clrscr();
	gs_p->tickCounter = 0;
	gs_p->mode = 0;
	gs_p->prevMode = 1;
	gs_p->gameInitialized = 0;
	initTimerStuff(); //Comment to debug
}

void modeSelect(gameStruct * gs_p){
	char input = get_key_pressed();

	switch(gs_p->mode){
	case(0):
		//Functions for main menu
		if(gs_p->prevMode != gs_p->mode){
			color(15, 0);
			clrscr();
			initMainMenu();
		}
		gs_p->mode = menuPicker(gs_p->mode, input);

		break;
	case(1):
		//Functions for singleplayer
		if(gs_p->prevMode != gs_p->mode){
			color(15, 0);
			clrscr();
			initGameUI();
		}
		if(gs_p->gameInitialized == 0) initializeGame(&gs_p, 1);
		break;
	case(2):
		//Functions for game (clear, update, draw...)
		if(gs_p->prevMode != gs_p->mode){
			color(15, 0);
			clrscr();
			initGameUI();
		}
		if(gs_p->gameInitialized == 0) initializeGame(&gs_p, 2);
		break;
	case(3):
		//Help menu
		gs_p->mode = menuPicker(gs_p->mode, input);
		color(15, 0);
		clrscr();
		helpMenu();
		break;
	case(4):
		//Functions for Boss key
		//Pause timer
		//Draw screen
		//EXIT on ESC (setMode = 2)
		break;
	default:
		gs_p->mode = 0;
	}

	gs_p->prevMode = gs_p->mode;
}

void initializeGame(gameStruct * gs_p, uint8_t numPlayers){
	//INIT CONTROL VARIABLES
	gs_p->spawnCounter = 0;
	gs_p->numPlayers = numPlayers;
	gs_p->gameInitialized= 1;

	//INIT TOP LEVEL STRUCTS
	init_entityHandler(&(gs_p->entityArray));
	initBulletManager(&(gs_p->bulletArray));
	initEnemyManager(&(gs_p->enemyArray));

	//ADD PLAYER - WITH SET NUMBER OF PLAYERS.
	pushEntity(&(gs_p->entHan),&(gs_p->playerEnt),0,40,23,0,0,0,0);
	initPlayer(&(gs_p->playerEnt), &(gs_p->player), gs_p->numPlayers);

	//INIT LCD (ONLY IF 2 PLAYERS)
	if(gs_p->numPlayers == 2){
		initLCD();
		lcd_clear_all(gs_p->LCDbuffer,0x00);
		lcd_push_buffer(gs_p->LCDbuffer);
	}

	//INIT CONTROLLER (do anyways for random seed)
	initController();
}

void clearGame(gameStruct * gs_p){
	if(gs_p->numPlayers == 2) lcd_clear_all(gs_p->LCDbuffer,0x00);
	clearAllEntities(&(gs_p->entHan));
	clearPlayer(&(gs_p->player));
}

void updateGameFromInputs(gameStruct * gs_p, char input){
	updatePlayerVel(&(gs_p->player), input);
	if(gs_p->numPlayers == 2) updateCrosshair(&(gs_p->player),readJoystick());
	updateEntities(&(gs_p->entHan));
}

void drawGame(gameStruct * gs_p){
	//LCD
	if(gs_p->numPlayers == 2){
		//con_draw_putty_to_lcd(&(gs_p->enemMan),&(gs_p->player),&(gs_p->LCDbuffer));
		lcd_push_buffer(gs_p->LCDbuffer);
	}
	//Putty
	drawAllEntities(&(gs_p->entHan));
	drawPlayer(&(gs_p->player));
}




