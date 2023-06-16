#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <stdio.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"  // Input/output library for this course
#include "vec.h"
#include "util.h"

// struct of type entity_t
// contains standard fields that all entities will have
// such as position, velocity, hp, and spriteIndex
// also has a setActive field, which is very useful for object pooling in our entity handler

typedef struct{
	vector_t pos;
	vector_t vel;
	uint8_t spriteIndex;
	uint8_t isActive;
	uint8_t entityIndex;
} entity_t;

void move(entity_t * ptr);
void updateVel(entity_t * ptr, int8_t x, int8_t y);
void setEntityVel(entity_t * ptr, int8_t x, int8_t y);
void setEntityPos(entity_t * ptr, int8_t x, int8_t y);
void damageEntity(entity_t * ptr, int8_t x);
void initEntity(entity_t * ptr, uint8_t spriteIndex, uint8_t x, uint8_t y);
void destroyEntity(entity_t * ptr);
void setSpriteIndex(entity_t * ptr, uint8_t index);
void calculateGravity(entity_t * bullet, entity_t * solidObj);


#endif	// JOYSTICK_H





