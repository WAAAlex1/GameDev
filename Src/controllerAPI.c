/*
 * controllerAPI.c
 *
 *  Created on: 14. jun. 2023
 *      Author: frede
 */

#include "controllerAPI.h"
#define DEADZONE 300
#define CENTER_X 1230
#define CENTER_Y 1310

uint8_t readJoystick(){
	uint16_t pot1 = readPot1();
	uint16_t pot2 = readPot2();

	/*
	 *  UP LEFT    = 0x80
	 *  UP RIGHT   = 0x02
	 *  UP         = 0x01
	 *
	 *  DOWN LEFT  = 0x20
	 *  DOWN RIGHT = 0x08
	 *  DOWN       = 0x10
	 *
	 *  LEFT       = 0x40
	 *  RIGHT      = 0x04
	 *  CENTER     = 0x00
	 */

	if(pot2 >= CENTER_Y + DEADZONE){
		if(pot1 <= CENTER_X - DEADZONE){
			return 0x80; //UP LEFT
		} else if(pot1 >= CENTER_X + DEADZONE){
			return 0x02; //UP RIGHT
		} else {
			return 0x01; //UP
		}
	} else if(pot2 <= CENTER_Y - DEADZONE) {
		if(pot1 <= CENTER_X - DEADZONE){
			return 0x20; //DOWN LEFT
		} else if(pot1 >= CENTER_X + DEADZONE){
			return 0x08; //DOWN RIGHT
		} else {
			return 0x10; //DOWN
		}
	} else {
		if(pot1 <= CENTER_X - DEADZONE){
			return 0x40; //LEFT
		} else if(pot1 >= CENTER_X + DEADZONE){
			return 0x04; //RIGHT
		} else {
			return 0x00; //CENTER
		}
	}

	return 0x00;
}

uint8_t readButton1(){
	return readButtons() & 0x01;
}

uint8_t readButton2(){
	return readButtons() >> 1;
}

