/**
 * PIXELBOARD
 *
 * This code is made for circular efects using HSV propieties and a litle bit of polar coordinates in NEOPIXEl matrix
 *
 * some considerations
 *  -this code is meant to be usable in wierd type matrix like a round one, ore one were the pixels are multiple leds and in a not symetric way 
 *  -this code asumes that data or START of your matrix is at the top 
 *  -you define your config at config.h
 *  -if your matrix is custom you still need your values of HEIGHT an WIDHT in PIXELSSS!
 *
 * @author Teo caetano
 * @version 0.1
 */




#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <FastLED.h>
#include <vector>
#include "efectos.h"
#include "graphics.h"
#include "config.h"
#include "pixeltypes.h"
#include "classFrame.h"

#define ROJO 0
#define NARANJA 32
#define AMARILLO 64
#define VERDE 96
#define AQUA 128
#define AZUL 160
#define PURPURA 192
#define ROSA 224


extern int br;
extern int newBr;
extern int sp;

extern int frame2PixelLedMap[FRAME_BUFFER_SIZE];
extern int ledsPerPixel_prueba[FRAME_BUFFER_SIZE];
extern uint8_t lienzoHue[FRAME_BUFFER_SIZE];
extern uint8_t lienzoSaturacion[FRAME_BUFFER_SIZE];
extern uint8_t lienzoValue[FRAME_BUFFER_SIZE];

extern classFrame algoo;


void serialCheck(); 
void subirSpeed();
void bajarSpeed();
void subirBrillo();
void bajarBrillo();

extern uint8_t frameBuffer[FRAME_BUFFER_SIZE][3];
extern CRGB leds[NUM_LEDS];

#endif
