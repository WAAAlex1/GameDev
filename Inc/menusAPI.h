/*
 * menusAPI.h
 *
 *  Created on: 13. jun. 2023
 *      Author: frede
 */

#ifndef MENUSAPI_H_
#define MENUSAPI_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ansi.h"
#include "highscore.h"
#include "serialRead.h"

int8_t pickItems(char key, uint8_t activeItem);
void printItems(uint8_t activeItem);
void printScores();

#endif /* MENUSAPI_H_ */
