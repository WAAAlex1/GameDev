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
#include "scoreCalc.h"
#include "gameUI.h"

void initGameUI(player_t *player, uint8_t gameLevel)
{
	color(15, 7);

	for(uint8_t i = 1; i <= 46; i++)
	{
		gotoxy(81, i);
		printf("                    ");
	}

	//HP
	color(0, 7);
	gotoxy(90, 2);
	printf("HP");
	showPlayerHealth(player);

	//Game level
	color(0, 7);
	gotoxy(88, 26);
	printf("LEVEL");
	showGameLevel(gameLevel);

	//POWERUP
	color(0, 7);
	gotoxy(88, 15);
	printf("POWER");
	gotoxy(88, 20);
	printf(" NONE ");
	color(0, 0);
	gotoxy(88, 17);
	printf("     ");
	gotoxy(88, 18);
	printf("     ");
	color(0, 7);

	//SCORE
	gotoxy(88, 30);
	printf("SCORE");

	//MENU NAVIGATION
	gotoxy(82, 41);
	printf("[ESC] - Main menu");
	gotoxy(84, 42);
	printf("'h' - Help menu");
}

void updateGameUI(player_t *player, gamescore_t *score,uint8_t gameLevel)
{
	static uint8_t prevHealth = 0;
	static uint8_t prevPowerUp = 0;
	static uint8_t prevLevel = 0;

	if(player->HP != prevHealth) showPlayerHealth(player);
	if(player->powerUp != prevPowerUp) showPlayerPowerUp(player);
	if(gameLevel != prevLevel) showGameLevel(gameLevel);
	showPlayerScore(score);

	prevHealth = player->HP;
	prevPowerUp = player->powerUp;
	prevLevel = gameLevel;
}

void showPlayerHealth(player_t *player)
{
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

void showPlayerPowerUp(player_t *player)
{
	color(0, 7);

	switch(player->powerUp){
		case 1: //MEDKIT
			gotoxy(88, 20);
			printf(" HEAL ");
			color(0, 2);
			break;
		case 2: //SHIELD
			gotoxy(88, 20);
			printf("SHIELD");
			color(0, 4);
			break;
		case 3: //MEGA BULLET
			gotoxy(88, 20);
			printf(" MEGA ");
			color(0, 1);
			break;
		default: //NONE
			gotoxy(88, 20);
			printf(" NONE ");
			color(0, 0);
			break;
	}

	gotoxy(88, 17);
	printf("     ");
	gotoxy(88, 18);
	printf("     ");
}

void showPlayerScore(gamescore_t *score){
	gotoxy(86, 32);
	color(0, 7);
	printf("%010lu", score->score);
}

void showGameLevel(uint8_t gameLevel)
{
	gotoxy(88,27);
	color(0, 7);
	printf("%02d",gameLevel);
}







































