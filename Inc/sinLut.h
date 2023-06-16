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

int16_t lutSin(int16_t degrees);
int16_t lutCos(int16_t degrees);
int32_t expand(int32_t i);
void printFix(int32_t i);

// === LUT DECLARATIONS ===
extern const signed short SIN[512];

#endif	// SINLUT_H
