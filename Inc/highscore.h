/*
 * highscore.h
 *
 *  Created on: 12. jun. 2023
 *      Author: frede
 */

#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void saveHighscore(char name[4], uint32_t score);
char* readHighscoreName(uint8_t place);
uint32_t readHighscore(uint8_t place);
void highscoreTestFunc();

#endif /* HIGHSCORE_H_ */
