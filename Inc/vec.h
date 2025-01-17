#ifndef VEC_H
#define VEC_H

#include "stdint.h"

typedef struct{
	int32_t x,y;
} vector_t;

void rotateVector(vector_t *v, int degrees);
void setVectorInt(vector_t *v, int32_t x, int32_t y);
int16_t getXint(vector_t *v);
int16_t getYint(vector_t *v);
void updateVectorInt(vector_t *v, int32_t x, int32_t y);

#endif	// VEC_H
