#include "joystick.h"

void initJoystick(){

	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	//RIGHT
	// Set pin PC0 to input
	GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input)
	GPIOC-> PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x02 - Pull-down)

	//LEFT
	// Set pin PC1 to input
	GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 – Input)
	GPIOC-> PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x02 - Pull-down)

	//UP
	// Set pin PA4 to input
	GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 – Input)
	GPIOA-> PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x02 - Pull-down)

	//DOWN
	// Set pin PB0 to input
	GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input)
	GPIOB-> PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x02 - Pull-down)

	//CENTER
	// Set pin PB5 to input
	GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (5 * 2)); // Set mode register (0x00 – Input,)
	GPIOB-> PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (5 * 2)); // Set push/pull register (0x02 - Pull-down)
}

uint8_t readJS(){

	uint8_t values = 0;
	values |= (GPIOA->IDR & (0x0001 << 4)) >> 4; //Read from pin PA4, shift 0(UP)
	values |= (GPIOB->IDR & (0x0001 << 0)) << 1; //Read from pin PB0, shift 1(DOWN)
	values |= (GPIOC->IDR & (0x0001 << 1)) << 1; //Read from pin PC1, shift 2(LEFT)
	values |= (GPIOC->IDR & (0x0001 << 0)) << 3; //Read from pin PC0, shift 3(RIGHT)
	values |= (GPIOB->IDR & (0x0001 << 5)) >> 1; //Read from pin PB5, shift 4(CENTER)

	return values;
}

void initLED(){
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

void RGBJoystick(uint8_t val){
	switch(val){
		case(1):
			setLED(0,1,0); //UP = GREEN
			break;

		case(2):
			setLED(1,0,0); //DOWN = RED
			break;

		case(4):
			setLED(0,1,1); //LEFT = CYAN
			break;

		case(8):
			setLED(1,0,1); //RIGHT = PURPLE
			break;

		case(16):
			setLED(1,1,0); //CENTER = YELLOW
			break;

		default:
			setLED(0,0,0);
	}
}
