#ifndef EFECTOS_H
#define EFECTOS_H

#include<Arduino.h>

void updatePixel(int pixel, int hue, int sat, int val);
void colorPleno(uint8_t hue, uint8_t sat, uint8_t val );
void borrar();
void efecto3(int speed, int type_colorTransition);

#endif
