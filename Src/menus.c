/*
 * menus.c
 *
 *  Created on: 13. jun. 2023
 *      Author: frede
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ansi.h"
#include "highscore.h"
#include "serialRead.h"
#include "menusAPI.h"
#include "menus.h"

void initMainMenu(){
	color(15, 0);
	gotoxy(38, 5);
	printf("Cosmic Broardside Battle");

	gotoxy(10, 40);
	printf(" 'w' and 's' to navigate the menu ");
	gotoxy(10, 41);
	printf(" [SPACE] to select ");

	printScores();
}

void helpMenu(){
	color(15, 0);

	gotoxy(46, 5);
	printf("Controls");

	gotoxy(10, 10);
	inverse(1);
	printf(" Player 1 controls ");
	inverse(0);

	gotoxy(10, 12);
	printf(" w - Move up ");
	gotoxy(10, 13);
	printf(" a - Move left ");
	gotoxy(10, 14);
	printf(" s - Move down ");
	gotoxy(10, 15);
	printf(" d - Move right ");
	gotoxy(10, 16);
	printf(" [SPACE] - Use powerup ");

	inverse(1);
	gotoxy(10, 20);
	printf(" Player 2 controls ");
	inverse(0);

	gotoxy(10, 22);
	printf(" joystick - Move crosshair ");
	gotoxy(10, 23);
	printf(" white button - Shoot ");
	gotoxy(10, 24);
	printf(" red button - Swap gunside ");

	gotoxy(72, 10);
	inverse(1);
	printf(" Only singleplayer ");
	inverse(0);

	gotoxy(72, 12);
	printf(" , - Shoot left ");
	gotoxy(72, 13);
	printf(" . - Shoot right ");

	gotoxy(10, 40);
	printf(" 'm' to return to main menu ");
}

uint8_t menuPicker(uint8_t mode, char input){
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
			break;
		case 2: //MULTIPLAYER
			break;
		case 3: //HELP MENU
			if(input == 'm'){
				return 0;
			}
			break;
		default :
			return mode;
	}

	return mode;
}

















