#include "vectored.h"

void initVector(vector_t *v, int16_t x1, int16_t y1){
	v->x = x1;
	v->y = y1;
}

void rotateVectorByReference(vector_t *v, int16_t angle){
	int32_t temp = v->x;
	v->x = temp * Cosinoid(angle) - v->y * Sinosoid(angle);
	v->y = temp * Sinosoid(angle) + v->y * Cosinoid(angle);
}
