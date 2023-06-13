// =====================================================================
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================

#ifndef REALLUT_H
#define REALLUT_H

#include <stdint.h>
#include <stdio.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"  // Input/output library for this course

// === LUT SIZES ===
#define SIN_SIZE 512

// === LUT DECLARATIONS ===
extern const signed short SIN[512];

// === FUNCTIONS

int32_t Sinosoid(int16_t x);
int32_t expand(int32_t i);
int32_t Cosinoid(int16_t x);
void printFix(int32_t i);


#endif	// REALLUT_H
