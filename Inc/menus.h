#ifndef MENUS_H_
#define MENUS_H_

#include "gameHandler.h"
#include <stdint.h>

void initMainMenu();
void helpMenu(uint8_t bool);
void bossScreen();
void initGameOverScreen(gameStruct_t * gs_p);
void gameOverScreen(gameStruct_t * gs_p, char input);

#endif /* MENUS_H_ */
