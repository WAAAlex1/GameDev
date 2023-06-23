#ifndef GAMEUI_H_
#define GAMEUI_H_

#include "scoreCalc.h"

void initGameUI(player_t *player, uint8_t gameLevel);
void updateGameUI(player_t *player, gamescore_t *score,uint8_t gameLevel);
void showPlayerHealth(player_t *player);
void showPlayerPowerUp(player_t *player);
void showPlayerScore(gamescore_t *score);
void showGameLevel(uint8_t gameLevel);

#endif /* GAMEUI_H_ */
