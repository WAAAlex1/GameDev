/*
 * gameUI.h
 *
 *  Created on: 19. jun. 2023
 *      Author: frede
 */

#ifndef GAMEUI_H_
#define GAMEUI_H_

void initGameUI();
void updateGameUI(player_t *player);
void showPlayerHealth(player_t *player);
void showPlayerPowerUp();
void showPlayerScore();

#endif /* GAMEUI_H_ */
