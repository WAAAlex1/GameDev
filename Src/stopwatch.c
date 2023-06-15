/*
 * stopwatch.c
 *
 *  Created on: 6. jun. 2023
 *      Author: georg
 */

#include "stdint.h"
#include "stdio.h"
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "stopwatch.h"


volatile stopwatch_t stopwatch;
volatile uint8_t LCD_Flag;

void initTimerStuff()
{
	RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;
	TIM15->CR1 = 0x0000; // Configure timer 15 and disable counter
	TIM15->ARR = 624; // Set reload value
	TIM15->PSC = 1023; // Set prescale value
	//assuming a systemclock of 64mhz this reload value and prescale will result in a 1/100 seconds upcounting-mode timeout period
	TIM15->CR1 = 0x0001; // Configure timer 15 and enable counter

	//Interupt part:
	TIM15->DIER |= 0x0001; // Enable timer 15 interrupts
	NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 1); // Set interrupt priority
	NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn); // Enable interrupt
}

void updateTimer()
{
	if(stopwatch.hundredsthsOfSeconds == 99)
	{
		stopwatch.hundredsthsOfSeconds = 0;
		if(stopwatch.seconds == 59)
		{
			stopwatch.seconds = 0;
			if(stopwatch.minutes == 59)
			{
				stopwatch.minutes = 0;
				stopwatch.hours++;
			}
			else
			{
				stopwatch.minutes++;
			}
		}
		else
		{
			stopwatch.seconds++;
		}
	}
	else
	{
		stopwatch.hundredsthsOfSeconds++;
	}
}

void toggleTimer()
{
	TIM15->CR1 	^= 1;
}

void stopTimer()
{
	TIM15->CR1 	&= ~1;
}

void resetStopwatch()
{
	stopwatch.hours = 0;
	stopwatch.minutes = 0;
	stopwatch.seconds = 0;
	stopwatch.hundredsthsOfSeconds = 0;
}

void TIM1_BRK_TIM15_IRQHandler(void)
{
	//do something here
	updateTimer(); //Uncomment this to use the stopwatch
	LCD_Flag = 1; //Uncomment this to use the scrolling LCD text stuff

	TIM15->SR &= ~(0x0001); //Clear the interupt bit
}
