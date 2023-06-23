#include "buzz.h"

void initBuzz(){
	RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2
	RCC->AHBENR  |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B

	TIM2->CR1 = 0x0000; // Configure timer 2 and disable counter
	TIM2->PSC = 1023; // Set prescale value
	//assuming a systemclock of 64mhz this reload value and prescale will result in a 1/100 seconds upcounting-mode timeout period
	TIM2->CR1 = 0x0001; // Configure timer 15 and enable counter

	TIM2->CCER  &= ~TIM_CCER_CC3P;   // Clear CCER register
	TIM2->CCER  |=  0x00000001 << 8; // Enable OC3 output
	TIM2->CCMR2 &= ~TIM_CCMR2_OC3M;  // Clear CCMR2 register
	TIM2->CCMR2 &= ~TIM_CCMR2_CC3S;
	TIM2->CCMR2 |=  TIM_OCMode_PWM1; // Set output mode to PWM1
	TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;
	TIM2->CCMR2 |=  TIM_OCPreload_Enable;

	//Set pin PB10 to alternate
	GPIOB->MODER &= ~(0x00000003 << (10 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000002 << (10 * 2));  // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOB->PUPDR &= ~(0x00000003 << (10 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (10 * 2));  // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1); //Map PWM to PB10
}

void setFreq(uint16_t freq) {
	uint32_t reload;

	if(!freq){
		reload = 64e6; //64*10^6
	} else {
		reload = ((64e6 / freq) / (2000 + 1)) - 1;
	}

	TIM2->ARR  =  reload;   // Set auto reload value
	TIM2->CCR3 =  reload/2; // Set compare register
	TIM2->EGR  |= 0x01;
}

void turnOffBuzz(){
	static uint16_t counter = 0;

	if(TIM2->ARR != 64e6){ //
		counter++;
	}

	if (counter == 1){ //Wait for 100 ms
		counter = 0;
		setFreq(0);
	}
}










