#ifndef BALL_H
#define BALL_H

#include "stdint.h"
#include "stdio.h"
#include "vec.h"
#include "ansi.h"

typedef struct{
	vector_t pos,vel;
} ball_t;

//Insert function declarations:
void setPos(ball_t * ball,int32_t x, int32_t y);
void setVel(ball_t * ball,int32_t x, int32_t y);
void updatePos(ball_t * ball, int32_t k);
void drawBall(ball_t * ball);
void initBall(ball_t * ball);
int collision(ball_t * ball,uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

#endif	// BALL_H
