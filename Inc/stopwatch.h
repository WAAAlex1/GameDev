/*
 * stopwatch.h
 *
 *  Created on: 6. jun. 2023
 *      Author: georg
 */

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include "stdint.h"
#include "stdio.h"
#include "stm32f30x_conf.h"
#include "30010_io.h"

typedef struct{
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
	uint8_t hundredsthsOfSeconds;
} stopwatch_t;

extern volatile stopwatch_t stopwatch;
extern volatile uint8_t LCD_Flag;

void initTimerStuff();
void updateTimer();
void toggleTimer();
void stopTimer();
void resetStopwatch();
void TIM1_BRK_TIM15_IRQHandler(void);


#endif /* STOPWATCH_H_ */
