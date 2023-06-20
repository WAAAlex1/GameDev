#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>
#include <stdio.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"  // Input/output library for this course
#include "LCD.h"

void initLED();
void clearLED();
void setLED(uint8_t x1, uint8_t x2, uint8_t x3);
void turnOffLED();

#endif	// JOYSTICK_H


