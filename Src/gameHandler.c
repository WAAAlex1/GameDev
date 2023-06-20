#include "PuttyLCDConverter.h"
#include "stdint.h"
#include "ansi.h"
#include "controller.h"
#include "controllerAPI.h"
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
#include "highscore.h"
#include "gameUI.h"
#include <stdio.h>
#include <stdlib.h>
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
	gs_p->cooldownCounter = 3;
	initTimerStuff(); //Comment to debug
	initController();
	srand( (unsigned)(lutSin(readPot1()) + lutCos(readPot2())) );
	initLCD();
	initLED();
	setLED(0, 0, 0);
}

void modeSelect(gameStruct_t * gs_p){
	char input = get_key_pressed();
	turnOffLED();

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
	case(1): //Singleplayer
		if(MODE_CHANGE){
			color(15, 0);
			clrscr();
			initGameUI();
			gs_p->prevMode = gs_p->mode;
			gs_p->playerNum = gs_p->mode;
		}
		if(gs_p->gameInitialized == 0) initializeGame(gs_p);
		gs_p->mode = modePicker(gs_p->mode, input, gs_p);

		runGame(gs_p, input);

		updateGameUI(&(gs_p->player), &(gs_p->score));
		break;
	case(2): //Multiplayer
		if(MODE_CHANGE){
			color(15, 0);
			clrscr();
			initGameUI();
			gs_p->prevMode = gs_p->mode;
			gs_p->playerNum = gs_p->mode;
		}
		if(gs_p->gameInitialized == 0) initializeGame(gs_p);
		gs_p->mode = modePicker(gs_p->mode, input, gs_p);

		runGame(gs_p, input);

		updateGameUI(&(gs_p->player), &(gs_p->score));
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
		//Boss key
		if(MODE_CHANGE){
			bossScreen();
			gs_p->prevMode = gs_p->mode;
		}
		gs_p->mode = modePicker(gs_p->mode, input, gs_p);
		break;
	case(5):
		if(MODE_CHANGE){
			initGameOverScreen(gs_p);
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
	gs_p->gameInitialized = 1;
	initScore(&(gs_p->score));

	//INIT TOP LEVEL STRUCTS
	init_entityHandler(&(gs_p->entHan),gs_p->entityArray);
	initBulletManager(&(gs_p->bulMan),gs_p->bulletArray);
	initEnemyManager(&(gs_p->enemMan),gs_p->enemyArray);

	//ADD PLAYER - WITH SET NUMBER OF PLAYERS.
	initEntity(&(gs_p->entityArray[0]),0,40,23,0,0,0,0);
	gs_p->entityArray[0].isActive = 1;
	initPlayer(&(gs_p->entityArray[0]), &(gs_p->player), gs_p->playerNum);

	//INIT LCD
	lcd_clear_all(gs_p->LCDbuffer,0x00);
	lcd_push_buffer(gs_p->LCDbuffer);

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
		case 2: //MULTIPLAYER
			if(input == 'h') return 3;
			else if(input == 0x1B){ //ESC
				gs_p->gameInitialized = 0;
				freeMallocEntities(gs_p);
				return 0;
			} else if(input == 'b' || input == 'B') return 4;
			if(gs_p->player.HP <= 0) return 5;
			break;
		case 3: //HELP MENU
			if(input == 'm'){
				if(gs_p->gameInitialized){
					freeMallocEntities(gs_p);
				}
				gs_p->gameInitialized = 0;
				return 0;
			} else if(input == 0x1B && gs_p->gameInitialized){ //ESC
				return gs_p->playerNum;
			} else if(input == 't'){
				return 5;
			} else if(input == 0x2A){ //'*'
				highscoreFlush();
			}
			break;
		case 4: //BOSS KEY
			if(input == 'b' || input == 'B'){
				return gs_p->playerNum;
			}
			break;
		case 5: //GAME OVER
			gameOverScreen(gs_p, input);
			if(input == ' '){
				freeMallocEntities(gs_p);
				gs_p->gameInitialized = 0;
				return 0;
			}
		default :
			return mode;
	}

	return mode;
}

void freeMallocEntities(gameStruct_t * gs_p){
	for(uint8_t i = 0; i < ENEMY_ARR_LENGTH; i++){
		free(gs_p->enemMan.enemyArray[i]->entity);
	}

	for(int i = 0; i < BULLET_ARR_LENGTH; i++) {
		free(gs_p->bulMan.bulletArray[i]->entity);
	}
}

void runGame(gameStruct_t * gs_p, char input){
	//Clear
	clearPlayer(&(gs_p->player));
	lcd_clear_all(gs_p->LCDbuffer,0x00);
	gotoxy(1, 3);
	printf("%04d", gs_p->cooldownCounter);

	//update playeractions based on inputs:
	if(gs_p->playerNum == 2) updateCrosshair(&(gs_p->player),readJoystick());

	switch(gs_p->playerNum){
		case 1:
			if(input == ',') gs_p->player.gunSide = 1;
			else if(input == '.') gs_p->player.gunSide = -1;
			else gs_p->player.gunSide = gs_p->player.gunSide;
			if(!(gs_p->cooldownCounter) && (input == ',' || input == '.')){
				gs_p->cooldownCounter = 10;
				setLED(0, 1, 0);
				playerShoot(&(gs_p->player),&(gs_p->bulMan),&(gs_p->entHan),0,gs_p->player.crosshairY);
			}
			break;
		case 2:
			if(readButton2()) changeGunside(&(gs_p->player));

			if(readButton1() && !(gs_p->cooldownCounter)){
				gs_p->cooldownCounter = 10;
				setLED(0, 1, 0);
				playerShoot(&(gs_p->player),&(gs_p->bulMan),&(gs_p->entHan),0,gs_p->player.crosshairY);
			}
			break;
		default:
			break;
	}
	if(input == ' ') usePowerUp(&(gs_p->player),&(gs_p->bulMan), &(gs_p->entHan));

	//update entities:
	updatePlayerVel(&(gs_p->player), input);
	updateEntities(&(gs_p->entHan));
	checkBulletCollision(&(gs_p->bulMan),&(gs_p->entHan), &(gs_p->score));
	checkPlayerCollision(&(gs_p->player),&(gs_p->entHan));

	//Create new entities
	enemiesShoot(&(gs_p->bulMan),&(gs_p->entHan),&(gs_p->enemMan));
	if(gs_p->spawnCounter == 20) {
		spawnRandom(&(gs_p->enemMan),&(gs_p->entHan));
		gs_p->spawnCounter = 0;
	}
	incrementCounter(&(gs_p->spawnCounter), 1);

	//Draw LCD
	if(gs_p->playerNum == 2){
		lcd_draw_crosshair(gs_p->LCDbuffer,gs_p->player.crosshairX,gs_p->player.crosshairY);
		con_draw_putty_to_lcd(&(gs_p->enemMan), &(gs_p->player),gs_p->LCDbuffer);
		lcd_push_buffer(gs_p->LCDbuffer);
	}


	//Draw PuTTY
	clearAllEntities(&(gs_p->entHan));

	drawAllEntities(&(gs_p->entHan));
	drawPlayer(&(gs_p->player));

	incrementScore(&(gs_p->score), 100);
}


















































