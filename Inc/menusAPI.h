#ifndef MENUSAPI_H_
#define MENUSAPI_H_

#include <stdint.h>

int8_t pickMainMenuItems(char key, uint8_t activeItem);
void printMainMenuItems(uint8_t activeItem);
void printScores();
void drawMenuSprites();

#endif /* MENUSAPI_H_ */
