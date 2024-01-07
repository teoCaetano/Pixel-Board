#ifndef FRAME_H
#define FRAME_H

#include "main.h"

int getMaxRadio();

void valueConstructor(int max);
extern uint8_t lienzoValue[FRAME_BUFFER_SIZE];

void saturacionConstructor(int max);
extern uint8_t lienzoSaturacion[FRAME_BUFFER_SIZE];
/*
    @brief it maps degrees to uint8
*/
void hueConstructor(uint8_t huemin, uint8_t huemax );
/*
    @brief is were to save the map values of linezoPoolar from 360 to 255
*/
extern uint8_t lienzoHue[FRAME_BUFFER_SIZE];

/*
    @brief it converts the coordenates of cartesian constructor to poolar coordenates and saves the in lienzo poolar
*/
void poolarConstructor(int Y, int X);
extern int lienzoPoolar[FRAME_BUFFER_SIZE][2];

/*
    @brief it saves the cartesian coordenates of every position of the array whit te axis of coordenates in the center
    if the matris is pair it counts the respective axis, as example in an odd matrix the position (0, 0) would exist, as in a pair matrix it doesnt
*/
/*
                pair
    (-2, 2)(-1, 2)(1, 2)(2, 2)
    (-2, 1)(-1, 1)(1, 1)(2, 1)
    (-2,-1)(-1,-1)(1,-1)(2,-1)
    (-2,-2)(-1,-2)(1,-2)(2,-2)
                odd
    (-2, 2)(-1, 2)(0, 2)(1, 2)(2, 2)
    (-2, 1)(-1, 1)(0, 1)(1, 1)(2, 1)
    (-2, 0)(-1, 0)(0, 0)(1, 0)(2, 0)
    (-2,-1)(-1,-1)(0,-1)(1,-1)(2,-1)
    (-2,-2)(-1,-2)(0,-2)(1,-2)(2,-2)
*/
void cartesianConstructor();

/*
    @brief saves the x and y coordinates of cartesianConstructor
*/
extern int lienzoCartesiano[FRAME_BUFFER_SIZE][2];

/*
    @brief meant to be run at void setup makes the array whit the positions of the leds for you to work whit
    or in case you have a custom matrix just uses the arrays you define in frame.c
    @param {bool} serpenty  true if the leds are wired serpenty like an S
    @param {bool} start  true if first led is at the right false if left
    @param {bool} simetria  true if your matrix is custom, like not simetric leds per pixel, or symetric
    @param {int} lesdPPixel  keep at 1 if if your pixels are 1 led, and 2 if the pixels are 2, and so on forth
*/
void matrixConstructor(bool serpenty, bool start,bool simetria, int lesdPPixel, bool round);
extern int frame2PixelLedMap[FRAME_BUFFER_SIZE];
extern int ledsPerPixel_prueba[FRAME_BUFFER_SIZE];
extern uint8_t lienzoHSV2[400][3];
extern uint8_t lienzoHSV[400][3];
extern uint8_t lienzoRGB[400][3];
extern uint8_t secEspiral[155][2];
extern uint8_t secCuadrado[318][2];

#endif