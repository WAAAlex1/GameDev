#include "scoreCalc.h"

void initScore(gamescore_t * Score){
	Score->score = 0;
}

void incrementScore(gamescore_t * Score, uint32_t points){
	if(Score->score >= 0xFAA2B57F){ //Make sure the score cannot overflow and hit 0 (optimistic to hit this score)
		Score->score = 0xFAA2B57F;
	} else {
		Score->score += points;
	}
}
