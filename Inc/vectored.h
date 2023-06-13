#ifndef VECTORED_H_
#define VECTORED_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"

typedef struct {
	int32_t x,y;
} vector_t;

void initVector(vector_t *v, int16_t x1, int16_t y1);

void rotateVectorByReference(vector_t *v, int16_t angle);

#endif /* VECTORED_H_ */
