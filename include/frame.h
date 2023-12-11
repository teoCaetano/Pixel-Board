#ifndef FRAME_H
#define FRAME_H

#include "efectos.h"
#include "graphics.h"
#include "config.h"
#include "pixeltypes.h"

extern int frame2PixelLedMap[FRAME_BUFFER_SIZE];
extern uint8_t lienzoHSV2[400][3];
extern uint8_t lienzoHSV[400][3];
extern uint8_t lienzoRGB[400][3];
extern uint8_t secEspiral[155][2];
extern uint8_t secCuadrado[318][2];

#endif