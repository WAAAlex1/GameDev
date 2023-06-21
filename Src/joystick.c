#include "joystick.h"
#include "LCD.h"

void initLED(){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	//PIN PA9 -> BLUE
	GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
	GPIOA->OSPEEDR |= (0x00000002 << (9 * 2)); // set speed register(0x02 - 2 MHz)
	GPIOA->OTYPER &= ~(0x0001 << (9)); // Clear output type register
	GPIOA->OTYPER |= (0x0000 << (9)); // Set output type register(0x00 - Push pull)
	GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000001 << (9 * 2)); // Set mode register(0x01 - Out)

	//PIN PB4 -> RED
	GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
	GPIOB->OSPEEDR |= (0x00000002 << (4 * 2)); // set speed register(0x02 - 2 MHz)
	GPIOB->OTYPER &= ~(0x0001 << (4)); // Clear output type register
	GPIOB->OTYPER |= (0x0000 << (4)); // Set output type register(0x00 - Push pull)
	GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register(0x01 - Out)


	//PIN PC7 -> GREEN
	GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
	GPIOC->OSPEEDR |= (0x00000002 << (7 * 2)); // set speed register(0x02 - 2 MHz)
	GPIOC->OTYPER &= ~(0x0001 << (7)); // Clear output type register
	GPIOC->OTYPER |= (0x0000 << (7)); // Set output type register(0x00 - Push pull)
	GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000001 << (7 * 2)); // Set mode register(0x01 - Out)
}

void clearLED(){
	GPIOB->ODR &= ~(0x0001 << 4); // Clear register
	GPIOC->ODR &= ~(0x0001 << 7); // Clear register
	GPIOA->ODR &= ~(0x0001 << 9); // Clear register
}

void setLED(uint8_t x1, uint8_t x2, uint8_t x3){
	//clear registers
	clearLED();

	//set registers
	if(!x1){GPIOB->ODR |= 0x0001 << 4;} //pin PB4 (RED)
	if(!x2){GPIOC->ODR |= 0x0001 << 7;} //pin PC7 (GREEN)
	if(!x3){GPIOA->ODR |= 0x0001 << 9;} //pin PA9 (BLUE)
}

void turnOffLED(){
	static uint16_t counter = 0;

	if(!(GPIOB->ODR & (0x0001 << 4)) || !(GPIOB->ODR & (0x0001 << 7)) || !(GPIOB->ODR & (0x0001 << 9))){ //If any LED is on
		counter++;
	}

	if (counter == 5){ //Wait for 500 ms
		counter = 0;
		setLED(0, 0, 0);
	}
}













