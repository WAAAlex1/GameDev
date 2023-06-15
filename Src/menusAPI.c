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

#include "ansi.h"
#include "highscore.h"
#include "serialRead.h"
#include "menusAPI.h"

int8_t pickItems(char key, uint8_t activeItem){
	if(key == 'w' && activeItem > 0){
		return -1;
	} else if (key == 's' && activeItem < 3){
		return 1;
	}

	return 0;
}

void printItems(uint8_t activeItem){
	//TITLE
	gotoxy(38, 5);
	printf("Cosmic Boardside Battle");

	//MENU ITEMS
	gotoxy(10, 10);
	if(activeItem == 0){ inverse(1); } else { inverse(0); }
	printf(" Singleplayer ");

	gotoxy(10, 15);
	if(activeItem == 1){ inverse(1); } else { inverse(0); }
	printf(" Multiplayer ");

	gotoxy(10, 20);
	if(activeItem == 2){ inverse(1); } else { inverse(0); }
	printf(" Help ");

	gotoxy(10, 25);
	if(activeItem == 3){ inverse(1); } else { inverse(0); }
	printf(" Exit ");

	inverse(0);
}

void printScores(){
	//HIGHSCORES
	//Read highscores
	char *highName0 = readHighscoreName(0);
	char *highName1 = readHighscoreName(1);
	char *highName2 = readHighscoreName(2);
	char *highName3 = readHighscoreName(3);
	char *highName4 = readHighscoreName(4);

	//Print highscores
	gotoxy(75, 10);
	printf("HIGHSCORES");
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

