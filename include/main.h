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
#include "efectos.h"
#include "graphics.h"
#include "config.h"
#include "pixeltypes.h"
#include "classTransition.h"
#include "main.h"
#include "frame.h"


extern int br;
extern int newBr;
extern int sp;

int bufferToPixeledBase(int x, int y);
int getLienzoH(int x, int y);
int getLienzoS(int x, int y);
int getLienzoV(int x, int y);
int getLienzoH2(int x, int y);
int getLienzoS2(int x, int y);
int getLienzoV2(int x, int y);
void serialCheck(); 
void subirSpeed();
void bajarSpeed();
void subirBrillo();
void bajarBrillo();

extern uint8_t frameBuffer[FRAME_BUFFER_SIZE][3];
extern CRGB leds[NUM_LEDS];

#endif
