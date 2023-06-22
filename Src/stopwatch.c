/*
 * stopwatch.c
 *
 *  Created on: 6. jun. 2023
 *      Author: georg
 */
#include "stdio.h"
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "stopwatch.h"

volatile uint8_t timer_Flag;

void initTimer()
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

void TIM1_BRK_TIM15_IRQHandler(void)
{
	timer_Flag = 1; //global flag

	TIM15->SR &= ~(0x0001); //Clear the interupt bit
}
