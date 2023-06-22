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
	uint8_t height;
	uint8_t spriteIndex;
	uint8_t isActive;
	uint8_t preX;
	uint8_t preY;
	uint8_t powerType; //0 = nothing, 1 = medkit [Green], 2 = shield [Blue], 3 = megabullet [Red]
} entity_t;

#define G 1 //int

void move(entity_t * ptr);
void updateVel(entity_t * ptr, int8_t x, int8_t y);
void setEntityVel(entity_t * ptr, int8_t x, int8_t y);
void setEntityVelFixed(entity_t *ptr, int32_t x, int32_t y);
void setEntityPos(entity_t * ptr, int16_t x, int16_t y);
void initEntity(entity_t * ptr, uint8_t spriteIndex, uint8_t xPos, int16_t yPos,int32_t xVel,int32_t yVel, uint8_t fixedVel, uint8_t height,uint8_t powerType);
void destroyEntity(entity_t * ptr);
void clearEntity(entity_t * ptr);
void drawEntity(entity_t * ptr, uint8_t powerType);
void calculateGravity(entity_t * bullet, entity_t * solidObj);
uint8_t detectEntityCollision(entity_t * player, entity_t * obj2);
void checkEntityPos(entity_t * ptr);

#endif





