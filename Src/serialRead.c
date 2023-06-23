#include "serialRead.h"

uint8_t get_key_pressed(){

	uint8_t temp = uart_get_char();
	if(uart_get_count() >= 3) uart_clear();

	switch(temp){
	case(0x1B): //esc
	case(0x2A): //'*'
	case(0x20): //Space
	case(0x2E): //Full Stop
	case(0x2c): //COMMA
		return(temp);
	default:
		return(temp >= 0x41 && temp <= 0x7A ? temp : 0x3F);
	}
}
