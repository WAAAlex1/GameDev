#include "vec.h"

/*
 * Vector is given in fixed point 18.14 number representation
 */
void rotateVector(vector_t *v, int degrees)
{
	int32_t temp = v->x;
	v->x = ((temp*lutCos(degrees)) >> 14) - ((v->y*lutSin(degrees)) >> 14);
	v->y = ((temp*lutSin(degrees)) >> 14) + ((v->y*lutCos(degrees)) >> 14);
}

/*
 * Takes x and y coordinates as integers an initializes the vectors values
 * as the fixed point 18.14 representation of those ints
 */
void setVector(vector_t *v, int32_t x, int32_t y)
{
	//Testing point values:
	v->x = x << 14;
	v->y = y << 14;
}

/*
 * Returns the integer part of the fixed point x coordinate
 */
int16_t getXint(vector_t *v)
{
	return v->x >> 14;
}

/*
 * Returns the integer part of the fixed point y coordinate
 */
int16_t getYint(vector_t *v)
{
	return v->y >> 14;
}
