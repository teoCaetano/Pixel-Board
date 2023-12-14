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

extern int efectoIdx;
extern int efectoIdxLast;
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
