#ifndef BUZZ_H_
#define BUZZ_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "stdint.h"

void initBuzz();
void setFreq(uint16_t freq);
void turnOffBuzz();

#endif /* BUZZ_H_ */
