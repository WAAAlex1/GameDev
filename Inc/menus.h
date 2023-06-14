/*
 * menus.h
 *
 *  Created on: 13. jun. 2023
 *      Author: frede
 */

#ifndef MENUS_H_
#define MENUS_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ansi.h"
#include "highscore.h"
#include "serialRead.h"
#include "menusAPI.h"

void mainMenu();

#endif /* MENUS_H_ */
