/*
 * stopwatch.h
 *
 *  Created on: 6. jun. 2023
 *      Author: georg
 */

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include "stdint.h"

extern volatile uint8_t timer_Flag;

void initTimer();
void TIM1_BRK_TIM15_IRQHandler(void);


#endif /* STOPWATCH_H_ */
