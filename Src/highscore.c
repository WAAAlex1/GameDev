/*
 * highscore.c
 *
 *  Created on: 12. jun. 2023
 *      Author: frede
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "ansi.h"
#include "highscore.h"

void saveHighscore(char name[], uint32_t score){
	uint16_t oldScores[20];
	uint8_t pos = 0;

	for(uint8_t i = 0; i < 20; i++){ //Copy all the old data into an array
		oldScores[i] = readMemory(i);
	}

	for(uint8_t i = 0; i < 5; i++){ //Check where a new score would fir into the array
		uint32_t oldScore = readMemory(i*4) | (readMemory(i*4 + 1) << 16);
		if(oldScore < score){
			break;
		}
		pos++;
	}

	if(pos == 5){ //Do not save if the score does not make the list
		return;
	}

	for(uint8_t i = 4; i > pos; i--){ //Shift all positions below the new score
		//Shift the score
		oldScores[i*4+0] = oldScores[(i-1)*4+0];
		oldScores[i*4+1] = oldScores[(i-1)*4+1];

		//Shift the name
		oldScores[i*4+2] = oldScores[(i-1)*4+2];
		oldScores[i*4+3] = oldScores[(i-1)*4+3];
	}

	//Save the new score
	oldScores[pos*4] = score & 0x0000FFFF;
	oldScores[pos*4 + 1] = score >> 16;

	oldScores[pos*4 + 3] = (name[0] << 8) | name[1];
	oldScores[pos*4 + 2] = (name[2] << 8) | name[3];

	//Write it to memory
	saveToMemory(oldScores, 20);
}

char* readHighscoreName(uint8_t place){
	if(place < 0 || place > 4){
		return NULL;
	}

	//Allocate space for name array
	char *name = malloc(5*sizeof(char));

	//Read name from memory and save to char array
	uint16_t temp = readMemory(4*place + 3);

	name[0] = temp >> 8;
	name[1] = temp & 0x00FF;

	temp = readMemory(4*place + 2);

	name[2] = temp >> 8;
	name[3] = temp & 0x00FF;
	name[4] = '\0';

	return name;
}

uint32_t readHighscore(uint8_t place){
	if(place < 0 || place > 4){
		return 0;
	}

	return readMemory(place*4) | readMemory(place*4 + 1) << 16;
}

void highscoreTestFunc(){
	uint16_t oldScores[20] = {0};

	saveToMemory(oldScores, 20);

	char *fred = "Fred";
	char *alex = "Alex";
	char *skil = "skil";
	char *isue = "isue";
	char *geor = "Geor";


	uint32_t sco0 = 4294967295;
	uint32_t sco1 = 420;
	uint32_t sco2 = 42;
	uint32_t sco3 = 7;
	uint32_t sco4 = 1;

	saveHighscore(fred, sco0);
	saveHighscore(alex, sco1);
	saveHighscore(skil, sco2);
	saveHighscore(isue, sco3);
	saveHighscore(geor, sco4);
}

/*void highscoreNamePrompt(char input, gamescore_t *score){
	static char *name = "____";

	color(15, 0);
	gotoxy(40, 21);
	printf("NEW HIGHSCORE");
	gotoxy(40, 23);
	printf("ENTER YOUR NAME");
	gotoxy(40, 24);
	printf("%c %c %c %c", name[0], name[1], name[2], name[3]);

	//Save the input if it is valid
	if(input != 0xF3){
		gotoxy(1, 3);
		printf("%c", input);
		for(uint8_t i = 0; i < 4; i++){
			if(name[i] == '_'){
				name[i] = input;
				//break;
			}
		}
	}

	//When the name is fully written, save it
	if(name[3] != '_' && input == ' '){
		saveHighscore(name, score->score);
		name = "____";
	}
}*/







































