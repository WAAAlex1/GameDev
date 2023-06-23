#ifndef ANSI_H_
#define ANSI_H_

#include "stdint.h"

void printTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t hundredsthsOfSeconds,uint8_t x, uint8_t y, char title[]);
void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor();
void clrscr();
void clreol();
void gotoxy(uint8_t x, uint8_t y);
void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);
void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char title[]);
void moveCursorX(uint8_t X, uint8_t UP);
void moveCursorY(uint8_t Y, uint8_t UP);
void invisibleCursor();

#endif /* ANSI_H_ */
