#include "entity.h"

// API - generic functions for manipulating and controlling our entity_t struct.


//moves a given entity by its velocity. (both in fixed point so easy to add).
void move(entity_t * ptr){
	ptr->pos.x += ptr->vel.x;
	ptr->pos.y += ptr->vel.y;
}

//updates the velocity of a given struct.
void updateVel(entity_t * ptr, int8_t x, int8_t y){
	updateVectorInt(&(ptr->vel),x,y);
}

// MAINLY USED FOR INIT: --------------------------------------------------

//function to initialize the values of an entity struct and set its spriteindex.
void initEntity(entity_t * ptr, uint8_t spriteIndex, uint8_t xPos, uint8_t yPos,uint8_t xVel,uint8_t yVel, uint8_t fixedVel, uint8_t height){
	setEntityPos(ptr,xPos,yPos);
	if(fixedVel)
	{
		setEntityVelFixed(ptr,xVel,yVel);
	}
	else
	{
		setEntityVel(ptr,xVel,yVel);
	}
	setSpriteIndex(ptr, spriteIndex);
	if(height >= 0 && height <= 3) ptr->height = height;
	ptr->isActive = 0;
}

void setEntityVel(entity_t * ptr, int8_t x, int8_t y){
	setVectorInt(&(ptr->vel),x,y);
}

void setEntityVelFixed(entity_t *ptr, int32_t x, int32_t y)
{
	ptr->vel.x = x;
	ptr->vel.y = y;
}

void setEntityPos(entity_t * ptr, int8_t x, int8_t y){
	setVectorInt(&(ptr->pos),x,y);
}

//function for setting an entity's spriteindex to a passed value.
void setSpriteIndex(entity_t * ptr, uint8_t index){
	if(index >= 0 && index <= 7){ptr->spriteIndex = index;}
}

//-------------------------------------------------------------------------


//function to "destroy" an entity by setting it inactive.
void destroyEntity(entity_t * ptr){
	ptr->isActive = 0;
}

void drawEntity(entity_t * ptr){
	ui_draw_sprite(ptr->spriteIndex, 15, 0, getXint(&(ptr->pos)), getYint(&(ptr->pos)));
}

void clearEntity(entity_t * ptr){
	ui_clear_sprite(ptr->spriteIndex, 15, 0, getXint(&(ptr->pos)), getYint(&(ptr->pos)));
}

//calculate gravity between two entities (bullet and an asteroid)
//using fixed point 18x14
void calculateGravity(entity_t * bullet, entity_t * solidObj){
	int32_t x1 = bullet->pos.x;
	int32_t y1 = bullet->pos.y;
	int32_t x2 = solidObj->pos.x;
	int32_t y2 = solidObj->pos.y;
	int32_t massObj;
	int32_t deltaX;
	int32_t deltaY;
	int32_t dist;

	switch(solidObj->entityIndex){
	case 3:
		massObj = 1 << 14;
		break;
	case 4:
		massObj = 9 << 14;
		break;
	case 5:
		massObj = 27 << 14;
		x2 += 3 << 13; //add 1.5 to center the 3x3 asteroid
		y2 += 3 << 13; //add 1.5 to center the 3x3 asteroid
		break;
	default:
		massObj = 0;
	}

	dist = getManDistance(x1>>14, y1>>14, x2>>14, y2>>14);
	if(dist > 20) return;
	// SKALER DELTAX OG DELTAY med konstant/dist^2
	deltaX = (x2-x1) * ( (((G)*(massObj) >> 14) << 14) / ((dist*dist) >> 14) ) >> 14;
	deltaY = (y2-y1) * ( (((G)*(massObj) >> 14) << 14) / ((dist*dist) >> 14) ) >> 14;

	//Finally add the gravity to our velocity vector for our bullet
	bullet->vel.x += deltaX;
	bullet->vel.y += deltaY;
}

int32_t centeredXPOS(entity_t * ptr){
	switch(ptr->spriteIndex){
		case(0): //add 2
		case(1): //add 2
			return ptr->pos.x + (2 << 14);
		case(2): //add 1.5
		case(5): //add 1.5
			return ptr->pos.x + (3 << 13);
		case(3): //add 0
		case(6): //add 0
			return ptr->pos.x + (0 << 14);
		case(4): //add 0.5
			return ptr->pos.x + (1 << 13);
		case(7): //add 1
			return ptr->pos.x + (1 << 14);
		default:
			return ptr->pos.x;
		}
}

int32_t centeredYPOS(entity_t * ptr){
	switch(ptr->spriteIndex){
		case(0): //add 1.5
		case(1): //add 1.5
			return ptr->pos.y + (3 << 13);
		case(2): //add 1
		case(5): //add 1
			return ptr->pos.y + (1 << 14);
		case(3): //add 0
		case(6): //add 0
		case(7): //add 0
			return ptr->pos.y + (0 << 14);
		case(4): //add 0.5
			return ptr->pos.y + (1 << 13);
		default:
			return ptr->pos.y;
		}
}


uint8_t detectEntityCollision(entity_t * obj1, entity_t obj2){
	int32_t x1_C = centeredXPOS(obj1);
	int32_t y1_C = centeredYPOS(obj1);
	int32_t x2_C = centeredXPOS(obj2);
	int32_t y2_C = centeredYPOS(obj2);
	int32_t minX1, minY1, minX2, minY2;

	//switch statement to set minX1 and minY1 values
	switch(obj1->spriteIndex){
		case(0): // 4x4
		case(1): // 4x4
			minX1 = 2 << 14; //2
			minY1 = 2 << 14; //2
			break;
		case(6): //1x1
			minX1 = 0;
			minY1 = 0;
			break;
		case(7): //3x1
			minX1 = 1 << 14; //1
			minY1 = 0 << 14; //0
			break;
		default:
			return 0;
	}
	//switch statement to set minX2 and minY2 values
	switch(obj2->spriteIndex){
		case(2): //4x3
		case(5): //4x3
			minX2 = 2 << 14; //2;
			minY2 = 1 << 14; //1;
		case(3): //1x1
			minX2 = 0 << 14;
			minY2 = 0 << 14;
		case(4): //2x2
			minX2 = 1 << 14; //1
			minY2 = 1 << 14; //1
		default:
			return 0;
	}

	if(absolute(x2_C - x1_C) <= (minX1 >= minX2 ? minX1 : minX2) || absolute(y2_C - y1_C) <= (minY1 >= minY2 ? minY1 : minY2)){
		return 1;
	}
	else return 0;
}

void checkEntityPos(entity_t * ptr){
	int16_t x = ptr->pos.x >> 14;
	int16_t y = ptr->pos.y >> 14;

	if(x < -5 || x > 81 || y > 47 || y < -5){
		ptr->isActive = 0;
	}
}
