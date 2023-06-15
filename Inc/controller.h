/*
 * controller.h
 *
 *  Created on: 14. jun. 2023
 *      Author: frede
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdint.h>

void initController();
uint16_t readPot1();
uint16_t readPot2();
void potsToString(char array[]);
uint8_t readButtons();


#endif /* CONTROLLER_H_ */
