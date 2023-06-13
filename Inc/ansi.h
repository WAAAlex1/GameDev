#ifndef _ANSI_H_
#define _ANSI_H_
#define ESC 0x1B

/* Includes -------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*Defines -----------------------------------------------------------------*/
void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor();
void clrscrn();
void clrRLine();
void gotoxy(uint8_t X, uint8_t Y);
void toggleInverse(uint8_t on);
void toggleBlink(uint8_t on);
void moveCursorX(uint8_t X, uint8_t UP);
void moveCursorY(uint8_t Y, uint8_t UP);
void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char title[], uint8_t style);
#endif
