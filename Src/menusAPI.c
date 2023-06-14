/*
 * menusAPI.c
 *
 *  Created on: 13. jun. 2023
 *      Author: frede
 */

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
	goToXY(38, 5);
	printf("Cosmic Boardside Battle");

	//MENU ITEMS
	goToXY(10, 10);
	if(activeItem == 0){ inverse(1); } else { inverse(0); }
	printf(" Singleplayer ");

	goToXY(10, 15);
	if(activeItem == 1){ inverse(1); } else { inverse(0); }
	printf(" Multiplayer ");

	goToXY(10, 20);
	if(activeItem == 2){ inverse(1); } else { inverse(0); }
	printf(" Help ");

	goToXY(10, 25);
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
	goToXY(75, 10);
	printf("HIGHSCORES");
	goToXY(72, 12);
	printf("%s: %010lu", highName0, readHighscore(0));
	goToXY(72, 14);
	printf("%s: %010lu", highName1, readHighscore(1));
	goToXY(72, 16);
	printf("%s: %010lu", highName2, readHighscore(2));
	goToXY(72, 18);
	printf("%s: %010lu", highName3, readHighscore(3));
	goToXY(72, 20);
	printf("%s: %010lu", highName4, readHighscore(4));

	//Free memory
	free(highName0);
	free(highName1);
	free(highName2);
	free(highName3);
	free(highName4);
}

