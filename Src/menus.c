/*
 * menus.c
 *
 *  Created on: 13. jun. 2023
 *      Author: frede
 */

#include "menus.h"

void mainMenu(){
	static uint8_t activeItem = 0;

	activeItem += pickItems(get_key_pressed(), activeItem);

	printItems(activeItem);
	printScores();
}


















