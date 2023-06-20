/*
 * menusAPI.c
 *
 *  Created on: 13. jun. 2023
 *      Author: frede
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <stdio.h>
#include <stdlib.h>

#include "PuTTYSprites.h"
#include "ansi.h"
#include "highscore.h"
#include "serialRead.h"
#include "menusAPI.h"

int8_t pickMainMenuItems(char key, uint8_t activeItem){
	if(key == 'w' && activeItem > 1){
		return -1;
	} else if (key == 's' && activeItem < 3){
		return 1;
	}

	return 0;
}

void printMainMenuItems(uint8_t activeItem){
	color(15, 0);

	//MENU ITEMS
	gotoxy(10, 10);
	if(activeItem == 1){ inverse(1); } else { inverse(0); }
	printf(" Singleplayer ");

	gotoxy(10, 15);
	if(activeItem == 2){ inverse(1); } else { inverse(0); }
	printf(" Multiplayer ");

	gotoxy(10, 20);
	if(activeItem == 3){ inverse(1); } else { inverse(0); }
	printf(" Help ");

	inverse(0);
}

void printScores(){
	color(15, 0);

	//Read highscores
	char *highName0 = readHighscoreName(0);
	char *highName1 = readHighscoreName(1);
	char *highName2 = readHighscoreName(2);
	char *highName3 = readHighscoreName(3);
	char *highName4 = readHighscoreName(4);

	//Print highscores
	gotoxy(74, 10);
	inverse(1);
	printf(" HIGHSCORES ");
	inverse(0);
	gotoxy(72, 12);
	printf("%s: %010lu", highName0, readHighscore(0));
	gotoxy(72, 14);
	printf("%s: %010lu", highName1, readHighscore(1));
	gotoxy(72, 16);
	printf("%s: %010lu", highName2, readHighscore(2));
	gotoxy(72, 18);
	printf("%s: %010lu", highName3, readHighscore(3));
	gotoxy(72, 20);
	printf("%s: %010lu", highName4, readHighscore(4));

	//Free memory
	free(highName0);
	free(highName1);
	free(highName2);
	free(highName3);
	free(highName4);
}

void drawMenuSprites(){
	ui_draw_sprite(0, 15, 0, 12, 28);
	ui_draw_sprite(1, 15, 0, 20, 28);
	ui_draw_sprite(2, 15, 0, 28, 29);
	ui_draw_sprite(3, 15, 0, 36, 30);
	ui_draw_sprite(4, 15, 0, 43, 29);
	ui_draw_sprite(5, 15, 0, 50, 28);
	ui_draw_sprite(6, 15, 0, 61, 30);
	ui_draw_sprite(7, 15, 0, 68, 30);

	color(15, 0);
	gotoxy(74, 29);
	inverse(1);
	printf(" Sprites ");
	inverse(0);

	gotoxy(10, 32);
	printf("Gun left");

	gotoxy(18, 33);
	printf("Gun right");

	gotoxy(26, 32);
	printf(" Enemy");

	gotoxy(34, 33);
	printf("S asteroid");

	gotoxy(42, 32);
	printf("M asteroid");

	gotoxy(50, 33);
	printf("L asteroid");

	gotoxy(58, 32);
	printf("Bullet");

	gotoxy(66, 33);
	printf("Mega bullet");
}











































