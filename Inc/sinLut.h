// =====================================================================
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================

#ifndef SINLUT_H
#define SINLUT_H

// === LUT SIZES ===
#define SIN_SIZE 512

#include "stdint.h"
#include "stdio.h"

int lutSin(int degrees);
int lutCos(int degrees);
int32_t expand(int32_t i);
void printFix(int32_t i);

// === LUT DECLARATIONS ===
extern const signed short SIN[512];

#endif	// SINLUT_H
