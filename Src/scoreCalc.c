#include "scoreCalc.h"

void initScore(gamescore_t * Score){
	Score->score = 0;
}

void incrementScore(gamescore_t * Score, uint16_t points){
	if(Score->score >= 0xFAA2B57F){ //Make sure the score cannot overflow and hit 0
		Score->score = 0xFAA2B57F;
	} else {
		Score->score += points;
	}
}
