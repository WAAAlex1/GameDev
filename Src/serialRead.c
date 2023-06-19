#include "serialRead.h"

uint8_t get_key_pressed(){

	uint8_t temp = uart_get_char();

	switch(temp){
	case(0x77): //w
		return(temp);
	case(0x61): //a
		return(temp);
	case(0x73): //s
		return(temp);
	case(0x64): //d
		return(temp);
	case(0x1B): //esc
		return(temp);
	case(0x68): //h
		return(temp);
	case(0x6D): //m
		return(temp);
	case(0x20): //Space
		return(temp);
	case(0x2E): //Full Stop
		return(temp);
	case(0x2c): //COMMA
		return(temp);
	default:
		return(temp >= 0x41 && temp <= 0x7A ? temp : 0xF3);
	}
}
