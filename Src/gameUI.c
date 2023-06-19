/*
 * gameUI.c
 *
 *  Created on: 19. jun. 2023
 *      Author: frede
 */

#include <stdint.h>
#include <stdio.h>
#include "ansi.h"
#include "player.h"
#include "gameUI.h"

void initGameUI(){
	color(15, 7);

	for(uint8_t i = 1; i <= 46; i++){
		gotoxy(81, i);
		printf("                    ");
	}

	color(0, 7);
	gotoxy(90, 2);
	printf("HP");

	gotoxy(88, 15);
	printf("POWER");

	gotoxy(88, 30);
	printf("SCORE");

	gotoxy(84, 40);
	printf("Return to menu");
	gotoxy(89, 42);
	printf("ESC");
}

void updateGameUI(player_t *player){
	showPlayerHealth(player);

}

void showPlayerHealth(player_t *player){
	color(7, 1);
	switch(player->HP){
		case 4:
			gotoxy(84, 4);
			printf("  ");
			gotoxy(88, 4);
			printf("  ");
			gotoxy(92, 4);
			printf("  ");
			gotoxy(96, 4);
			color(7, 4);
			printf("  ");
			break;
		case 3:
			gotoxy(84, 4);
			printf("  ");
			gotoxy(88, 4);
			printf("  ");
			gotoxy(92, 4);
			printf("  ");
			gotoxy(96, 4);
			color(7, 0);
			printf("  ");
			break;
		case 2:
			gotoxy(84, 4);
			printf("  ");
			gotoxy(88, 4);
			printf("  ");
			gotoxy(92, 4);
			color(7, 0);
			printf("  ");
			gotoxy(96, 4);
			printf("  ");
			break;
		case 1:
			gotoxy(84, 4);
			printf("  ");
			gotoxy(88, 4);
			color(7, 0);
			printf("  ");
			gotoxy(92, 4);
			printf("  ");
			gotoxy(96, 4);
			printf("  ");
			break;
		default:
			gotoxy(84, 4);
			color(7, 0);
			printf("  ");
			gotoxy(88, 4);
			printf("  ");
			gotoxy(92, 4);
			printf("  ");
			gotoxy(96, 4);
			printf("  ");
			break;
	}
}

void showPlayerPowerUp(){

}

void showPlayerScore(){

}






































