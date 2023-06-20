#include "serialRead.h"

uint8_t get_key_pressed(){

	uint8_t temp = uart_get_char();

	switch(temp){
	case(0x1B): //esc
		return(temp);
	case(0x20): //Space
		return(temp);
	case(0x2E): //Full Stop
		return(temp);
	case(0x2c): //COMMA
		return(temp);
	case(0x2A): //'*'
		return(temp);
	default:
		return(temp >= 0x41 && temp <= 0x7A ? temp : 0x3F);
	}
}
