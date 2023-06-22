/*
 * gameUI.h
 *
 *  Created on: 19. jun. 2023
 *      Author: frede
 */

#ifndef GAMEUI_H_
#define GAMEUI_H_

#include "scoreCalc.h"

void initGameUI(player_t *player);
void updateGameUI(player_t *player, gamescore_t *score);
void showPlayerHealth(player_t *player);
void showPlayerPowerUp(player_t *player);
void showPlayerScore(gamescore_t *score);

#endif /* GAMEUI_H_ */
