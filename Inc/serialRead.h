#ifndef SERIALREAD_H_
#define SERIALREAD_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "stdio.h"
#include "stdint.h"
#include "string.h"

uint8_t get_key_pressed();

#endif /* SERIALREAD_H_ */
