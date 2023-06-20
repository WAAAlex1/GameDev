/*
 * highscore.h
 *
 *  Created on: 12. jun. 2023
 *      Author: frede
 */

#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#include "scoreCalc.h"
#include <stdint.h>

void saveHighscore(char name[], uint32_t score);
char* readHighscoreName(uint8_t place);
uint32_t readHighscore(uint8_t place);
void highscoreTestFunc();
//void highscoreNamePrompt(char input, gamescore_t *score);

#endif /* HIGHSCORE_H_ */
