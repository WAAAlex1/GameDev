/*
 * menus.h
 *
 *  Created on: 13. jun. 2023
 *      Author: frede
 */

#ifndef MENUS_H_
#define MENUS_H_

#include <stdint.h>

void initMainMenu();
void helpMenu();
uint8_t menuPicker(uint8_t mode, char input);

#endif /* MENUS_H_ */
