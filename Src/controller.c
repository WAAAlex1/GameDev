/*
 * controller.c
 *
 *  Created on: 14. jun. 2023
 *      Author: frede
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <string.h>
#include "controller.h"

void initController(){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C


	// Set pin PA4 to input
	GPIOA->MODER |=  (0x00000000 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
	GPIOA->PUPDR |=  (0x00000002 << (4 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// Set pin PB0 to input
	GPIOB->MODER |=  (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOB->PUPDR |=  (0x00000002 << (0 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// Set pin PC10
	GPIOC->MODER &= ~(0x00000003 << (10 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (10 * 2));  // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (10 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (10 * 2));  // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// Set pin PC12
	GPIOC->MODER &= ~(0x00000003 << (12 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (12 * 2));  // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (12 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (12 * 2));  // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	//Pots
	RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
	RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
	RCC->AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12

	ADC1->CR = 0x00000000; // Clear CR register
	ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
	ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

	ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
	for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds

	ADC1->CR |= 0x80000000; // Start ADC1 calibration
	while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
	for (int i = 0 ; i < 100 ; i++) {} // Wait for a little while

	ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
	while (!(ADC1->ISR & 0x00000001)); // Wait until ready
}

uint16_t readPot1(){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_1Cycles5);
	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read

	return ADC_GetConversionValue(ADC1); // Read the ADC value
}

uint16_t readPot2(){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_1Cycles5);
	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read

	return ADC_GetConversionValue(ADC1); // Read the ADC value
}

void potsToString(char array[]){
	sprintf(array, "Pot1: %04hd | Pot2: %04hd\n", readPot1(), readPot2());
}

uint8_t readButtons(){
	uint8_t temp = 0;

	//The two buttons get returned as 000000XY
	temp |= (GPIOC->IDR & (0x0001 << 10)) >> 10; //bit 0
	temp |= (GPIOC->IDR & (0x0001 << 12)) >> 11; //bit 1

	return temp;
}











