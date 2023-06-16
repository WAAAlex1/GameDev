#ifndef PUTTYSPRITES_H_
#define PUTTYSPRITES_H_

#include <stdint.h>

// DEFINES:

void ui_draw_sprite(uint8_t index, uint8_t FGC, uint8_t BGC, uint8_t x, uint8_t y);
void ui_clear_sprite(uint8_t index, uint8_t FGC, uint8_t BGC, uint8_t x, uint8_t y);

#endif /* PUTTYSPRITES_H_ */
