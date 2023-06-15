#include "stdint.h"
#include "stdio.h"
#include "vec.h"
#include "ansi.h"
#include "ball.h"

void setPos(ball_t * ball,int32_t x, int32_t y)
{
	initVector(&(ball->pos),x,y);
}

void setVel(ball_t * ball,int32_t x, int32_t y)
{
	initVector(&(ball->vel),x,y);
}

void initBall(ball_t * ball)
{
	vector_t pos;
	vector_t vel;
	ball->pos = pos;
	ball->vel = vel;
}


void updatePos(ball_t * ball, int32_t k)
{
	ball->pos.x = ball->pos.x + (((k << 14)*ball->vel.x) >> 14);
	ball->pos.y = ball->pos.y + (((k << 14)*ball->vel.y) >> 14);
}

void drawBall(ball_t * ball)
{
	gotoxy(ball->pos.x >> 14,ball->pos.y >> 14);
	printf("o");
}

int collision(ball_t * ball,uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	//temps
	int32_t x = ball->pos.x >> 14;
	int32_t y = ball->pos.y >> 14;

	//Corner cases:
	if(x  == x1+1 && y == y1+1){return 3;}
	if(x == x2-1 && y == y1+1){return 3;}
	if(x == x1+1 && y == y2-1){return 3;}
	if(x == x2-1 && y == y2-1){return 3;}

	//Wall cases:
	if(x <= x1+1 || x >= x2-1){return 1;}
	if(y <= y1+1 || y >= y2-1){return 2;}

	//No collision:
	return 0;
}
