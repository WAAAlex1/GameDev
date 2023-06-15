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

#include "ansi.h"
#include "highscore.h"
#include "serialRead.h"
#include "menusAPI.h"
#include "menus.h"

void mainMenu(){
	static uint8_t activeItem = 0;

	activeItem += pickItems(get_key_pressed(), activeItem);

	printItems(activeItem);
	printScores();
}


















