#include "scoreCalc.h"

void initScore(gamescore_t * Score){
	Score->score = 0;
}

void incrementScore(gamescore_t * Score){
	Score->score++;
}
