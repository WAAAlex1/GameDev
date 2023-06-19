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

//bullet should be pulled in x-dir when range x <= 32
//bullet should be pulled in y-dir when range y <= 16
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
		massObj = 1;
		break;
	case 4:
		massObj = 9;
		break;
	case 5:
		massObj = 27;
		x2 += 3 << 13; //add 1.5 to center the 3x3 asteroid
		y2 += 3 << 13; //add 1.5 to center the 3x3 asteroid
		break;
	default:
		massObj = 0;
	}

	dist = getManDistance(x1>>14, y1>>14, x2>>14, y2>>14);
	if(dist > 20) return;
	// SKALER DELTAX OG DELTAY med konstant/dist^2
	deltaX = (x2-x1) * ((G << 14) / ((dist)*(dist) >> 14)) >> 14;
	deltaY = (y2-y1) * ((G << 14) / ((dist)*(dist) >> 14)) >> 14;

	//Finally add the gravity to our velocity vector for our bullet
	bullet->vel.x += deltaX;
	bullet->vel.y += deltaY;
}

int32_t centeredXPOS(entity_t * ptr){
	switch(ptr->spriteIndex){
		case(0):
		case(1):
		case(2):
		case(5): //cases for len x = 4 (add 2)
			return ptr->pos.x + (2 << 14);
		case(6):
		case(3): //cases for len x = 1 (add 0.5)
			return ptr->pos.x + (1 << 13);
		case(4): //cases for len x = 2 (add 1)
			return ptr->pos.x + (1 << 14);
		case(7): //cases for len x = 3 (add 1.5)
			return ptr->pos.x + (3 << 13);
		default:
			return ptr->pos.x;
		}
}
/*
int32_t centeredYPOS(entity_t * ptr){
	switch(ptr->spriteIndex){
		case(0):
		case(1)://cases for len y = 4 (add 2)
			return ptr->pos.y + (2 << 14);
		case(3):
		case(6):
		case(7): //cases for len y = 1 (add 0.5)
			return ptr->pos.y + (1 << 13);
		case(4): //cases for len y = 2 (add 1)
			return ptr->pos.y + (1 << 14);
		case(2):
		case(5): //cases for len y = 3 (add 1.5)
			return ptr->pos.y + (3 << 13);
		default:
			return ptr->pos.y;
		}
}

void detectEntityCollision(entity_t * obj1, entity_t obj2){
	int32_t x1_C = centeredXPOS(obj1);
	int32_t y1_C = centeredYPOS(obj1);
	int32_t x2_C = centeredXPOS(obj2);
	int32_t y2_C = centeredYPOS(obj2);
	int32_t minX, minY;

	switch(obj1->spriteIndex){
	case(0):
	case(1):
		if(obj2->spriteIndex == 6)
		break;
	case(6):

		break;
	case(2):
	case(5):

		break;
	case(4):

		break;
	default:
		return;
	}



	//only make checks if the two entities are within 4 in x and 4 in y of each other.
	if(absolute(x2-x1) <= 4 && absolute(y2-y1) <= 4){

	}
}
*/


