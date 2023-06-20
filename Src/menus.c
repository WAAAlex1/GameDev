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

#include "scoreCalc.h"
#include "gameHandler.h"
#include "ansi.h"
#include "highscore.h"
#include "serialRead.h"
#include "menusAPI.h"
#include "menus.h"

void initMainMenu(){
	color(15, 0);
	gotoxy(38, 5);
	printf("Cosmic Broadside Battle");

	gotoxy(10, 40);
	printf(" 'w' and 's' to navigate the menu ");
	gotoxy(10, 41);
	printf(" [SPACE] to select ");

	printScores();
}

void helpMenu(uint8_t bool){
	color(15, 0);

	gotoxy(46, 5);
	printf("Controls");

	gotoxy(10, 10);
	inverse(1);
	printf(" Player 1 controls ");
	inverse(0);

	gotoxy(10, 12);
	printf(" 'w' - Move up ");
	gotoxy(10, 13);
	printf(" 'a' - Move left ");
	gotoxy(10, 14);
	printf(" 's' - Move down ");
	gotoxy(10, 15);
	printf(" 'd' - Move right ");
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

	gotoxy(72, 20);
	inverse(1);
	printf(" Only in games ");
	inverse(0);

	gotoxy(72, 22);
	printf("'b' - Boss key");

	gotoxy(10, 40);
	printf(" 'm' to return to main menu ");

	if(bool){
		gotoxy(10, 41);
		printf(" [ESC] to return to game ");
	}

	drawMenuSprites();

	color(1, 7);
	inverse(1);
	gotoxy(55, 40);
	printf(" Write '*' ([SHIFT] + ') inside this  ");
	gotoxy(55, 41);
	printf(" menu to flush the leaderboard scores ");
	inverse(0);
}

void bossScreen(){
	color(0, 4);
	clrscr();

	gotoxy(5, 5);
	color(15, 4);
	printf("A problem has been detected and Windows has been shut down to prevent damage to your");
	gotoxy(5, 6);
	printf("computer.");

	gotoxy(5, 11);
	printf("UNMOUNTABLE_BOOT_VOLUME");

	gotoxy(5, 16);
	printf("If this is the first time you're seeing this error screen, restart your computer. If this");
	gotoxy(5, 17);
	printf("screen appears again, follow these steps:");

	gotoxy(5, 22);
	printf("Check to make sure any new hardware or software is properly installed. If this is a");
	gotoxy(5, 23);
	printf("new installation, ask your hardware or software manufacturer for any Windows updates you");
	gotoxy(5, 24);
	printf("might need.");

	gotoxy(5, 29);
	printf("If problems continue, disable or remove any newly installed hardware or software. Disable");
	gotoxy(5, 30);
	printf("BIOS memory options such as caching or shadowing. If you need to use Safe Mode to remove or");
	gotoxy(5, 31);
	printf("disable components, restart your computer, press F8 to select Advanced Startup Options, and");
	gotoxy(5, 32);
	printf("then select Safe Mode.");

	gotoxy(5, 37);
	printf("Technical Information:");

	gotoxy(5, 42);
	printf("*** STOP: 0x5448414E (0x4B594F55, 0x464F5250, 0x4C415949, 0x4E473A29)");
}

void initGameOverScreen(gameStruct_t * gs_p){
	color(15, 0);
	clrscr();

	gotoxy(46, 5);
	printf("GAME OVER");

	gotoxy(10, 10);
	inverse(1);
	printf(" Your score: %010lu ", gs_p->score.score);
	inverse(0);

	gotoxy(10, 40);
	if(gs_p->score.score > readHighscore(4)){
		printf("Write your name using the keyboard and press [SPACE] to return to main menu ");
		gotoxy(16, 13);
		printf("Your name:");
	} else {
		printf("Press [SPACE] to return to main menu");
	}

	printScores();
}

void gameOverScreen(gameStruct_t * gs_p, char input){
	static char name[] = {'_', '_', '_', '_'};

	color(15, 0);
	if(gs_p->score.score > readHighscore(4)){
		gotoxy(17, 15);
		printf("%c %c %c %c", name[0], name[1], name[2], name[3]);

		for(uint8_t i = 0; i < 4; i++){ //Write your name
			if(input != 0x3F && name[i] == 0x5F){
				name[i] = input;
				break;
			}
		}

		if(input == 0x20){ //Save highscore when you press space
			saveHighscore(name, gs_p->score.score);
			for(uint8_t i = 0; i < 4; i++){ //And reset the name for next round
				name[i] = '_';
			}
		}
	}


}
















