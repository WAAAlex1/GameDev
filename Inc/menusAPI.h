/*
 * menusAPI.h
 *
 *  Created on: 13. jun. 2023
 *      Author: frede
 */

#ifndef MENUSAPI_H_
#define MENUSAPI_H_

#include <stdint.h>

int8_t pickItems(char key, uint8_t activeItem);
void printItems(uint8_t activeItem);
void printScores();

#endif /* MENUSAPI_H_ */
