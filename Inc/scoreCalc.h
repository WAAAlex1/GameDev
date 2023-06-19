#ifndef SCORECALC_H_
#define SCORECALC_H_

#include <stdint.h>
#include <stdio.h>

typedef struct{
	uint32_t score;
}gamescore_t;

void initScore(gamescore_t * Score);
void incrementScore(gamescore_t * Score);


#endif /* SCORECALC_H_ */