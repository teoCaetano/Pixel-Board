#ifndef EFECTOS_H
#define EFECTOS_H

#include<Arduino.h>

void updatePixel(int pixel, int hue, int sat, int val);
void colorPleno(uint8_t hue, uint8_t sat, uint8_t val );
void borrar();
/*
*   @param {bool} enable_colorTransition - enables the color transition(true for yes, false for no)
*   @param {int} speed_colorTransition - it defines the max speed of the color transition (miliseconds)
*   @param {int} type_colorTransition - chooses the function which the color transition works
*   @param {bool} absolut_colorTransition - true for the absolut value of the function, false for only positive
*   @param {bool} enable_brightnessTransition - enables the brightness transition(true for yes, false for no)
*   @param {int} speed_brightnessTransition - it defines the max speed of the brightness transition (miliseconds)
*   @param {int} type_brightnessTransition - chooses the function which the brightness transition works
*   @param {bool} absolute_brightnessTransition - true for the absolut value of the function, false for only positive
*/
void efecto3(bool enable_colorTransition, int speed_colorTransition, int type_colorTransition, bool absolut_colorTransition ,bool enable_brightnessTransition , int speed_brightnessTransition, int type_brightnessTransition, bool absolut_brightnessTransition);

#endif
