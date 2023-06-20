#include "PuttyLCDConverter.h"
#include "stdint.h"
#include "ansi.h"
#include "controller.h"
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
#include "joystick.h"
#include "serialRead.h"
#include "gameUI.h"
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
	invisibleCursor();
	uart_clear();
	color(15, 0);
	clrscr();
	gs_p->tickCounter = 0;
	gs_p->mode = 0;
	gs_p->prevMode = 1;
	gs_p->gameInitialized = 0;
	gs_p->playerNum = 0;
	initTimerStuff(); //Comment to debug
	initController();
	initLED();
	setLED(0, 0, 0);
}

void modeSelect(gameStruct_t * gs_p){
	char input = get_key_pressed();

	switch(gs_p->mode){
	case(0):
		//Functions for main menu
		if(MODE_CHANGE){
			color(15, 0);
			clrscr();
			initMainMenu();
			gs_p->prevMode = gs_p->mode;
		}
		gs_p->mode = modePicker(gs_p->mode, input, gs_p);

		break;
	case(1):
		//Functions for singleplayer
		if(MODE_CHANGE){
			color(15, 0);
			clrscr();
			initGameUI();
			gs_p->prevMode = gs_p->mode;
			gs_p->playerNum = gs_p->mode;
		}
		if(gs_p->gameInitialized == 0) initializeGame(gs_p);
		gs_p->mode = modePicker(gs_p->mode, input, gs_p);
		break;
	case(2):
		//Functions for game (clear, update, draw...)
		if(MODE_CHANGE){
			color(15, 0);
			clrscr();
			initGameUI();
			gs_p->prevMode = gs_p->mode;
			gs_p->playerNum = gs_p->mode;
		}
		if(gs_p->gameInitialized == 0) initializeGame(gs_p);
		gs_p->mode = modePicker(gs_p->mode, input, gs_p);
		break;
	case(3):
		//Help menu
		if(MODE_CHANGE){
			color(15, 0);
			clrscr();
			helpMenu(gs_p->gameInitialized);
			gs_p->prevMode = gs_p->mode;
		}
		gs_p->mode = modePicker(gs_p->mode, input, gs_p);
		break;
	case(4):
		if(MODE_CHANGE){
			bossScreen();
			gs_p->prevMode = gs_p->mode;
		}
		gs_p->mode = modePicker(gs_p->mode, input, gs_p);
		break;
	default:
		gs_p->mode = 0;
	}

}

void initializeGame(gameStruct_t * gs_p){
	//INIT CONTROL VARIABLES
	gs_p->spawnCounter = 0;
	gs_p->gameInitialized= 1;

	//INIT TOP LEVEL STRUCTS
	init_entityHandler(&(gs_p->entHan),gs_p->entityArray);
	initBulletManager(&(gs_p->bulMan),gs_p->bulletArray);
	initEnemyManager(&(gs_p->enemMan),gs_p->enemyArray);

	//ADD PLAYER - WITH SET NUMBER OF PLAYERS.
	initEntity(&(gs_p->entityArray[0]),0,40,23,0,0,0,0);
	gs_p->entityArray[0].isActive = 1;
	initPlayer(&(gs_p->entityArray[0]), &(gs_p->player), gs_p->playerNum);

	//INIT LCD (ONLY IF 2 PLAYERS)
	if(gs_p->playerNum == 2){
		initLCD();
		lcd_clear_all(gs_p->LCDbuffer,0x00);
		lcd_push_buffer(gs_p->LCDbuffer);
	}
}

void clearGame(gameStruct_t * gs_p){
	if(gs_p->playerNum == 2) lcd_clear_all(gs_p->LCDbuffer,0x00);
	clearAllEntities(&(gs_p->entHan));
	clearPlayer(&(gs_p->player));
}

void updateGameFromInputs(gameStruct_t * gs_p, char input){
	updatePlayerVel(&(gs_p->player), input);
	if(gs_p->playerNum == 2) updateCrosshair(&(gs_p->player),readJoystick());
	updateEntities(&(gs_p->entHan));
}

void drawGame(gameStruct_t * gs_p){
	//LCD
	if(gs_p->playerNum == 2){
		con_draw_putty_to_lcd(&(gs_p->enemMan),&(gs_p->player),gs_p->LCDbuffer);
		lcd_push_buffer(gs_p->LCDbuffer);
	}
	//Putty
	drawAllEntities(&(gs_p->entHan));
	drawPlayer(&(gs_p->player));
}

uint8_t modePicker(uint8_t mode, char input, gameStruct_t * gs_p){
	static uint8_t activeItem = 1;

	switch(mode){
		case 0: //MAIN MENU
			activeItem += pickMainMenuItems(input, activeItem);
			printMainMenuItems(activeItem);

			if(input == ' '){
				return activeItem;
			}
			break;
		case 1: //SINGLEPLAYER
			if(input == 'h'){
				return 3;
			} else if(input == 0x1B){ //ESC
				return 0;
			} else if(input == 'b' || input == 'B'){
				return 4;
			}
			break;
		case 2: //MULTIPLAYER
			if(input == 'h'){
				return 3;
			} else if(input == 0x1B){ //ESC
				return 0;
			} else if(input == 'b' || input == 'B'){
				return 4;
			}
			break;
		case 3: //HELP MENU
			if(input == 'm'){
				gs_p->gameInitialized = 0;
				return 0;
			} else if(input == 0x1B && gs_p->gameInitialized){ //ESC
				return gs_p->playerNum;
			}
			break;
		case 4:
			if(input == 'b' || input == 'B'){
				return gs_p->playerNum;
			}
			break;
		default :
			return mode;
	}

	return mode;
}





