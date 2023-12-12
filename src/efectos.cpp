#include <Arduino.h>
#include <FastLED.h>
#include "efectos.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "frame.h"

void updatePixel(int pixel, int hue, int sat, int val) {
  if (val<0)
    val=0;
  else if (val >255)
    val=255;
  if (pixel>=0 && pixel < 400) {  
    frameBuffer[pixel][0]=hue;
    frameBuffer[pixel][1]=sat;
    frameBuffer[pixel][2]=val;
  }
}

void colorPleno(uint8_t hue, uint8_t sat, uint8_t val  ) {
    for (int y=0; y<20; y++) {
      for (int x=0; x<20; x++) {
        int l=getBufferIndex(x, y);
        updatePixel(l, hue, sat, val);
      }
   }
  
}

void borrar() {
  uint8_t hue=200;
  uint8_t sat=200;
  uint8_t val=200;
    for (int y=0; y<20; y++) {
      for (int x=0; x<20; x++) {
        int l=getBufferIndex(x, y);
        hue=getLienzoH(x,y);
        sat=getLienzoS(x,y);
        val=getLienzoV(x,y)/2;
        updatePixel(l, hue, sat, val);
      }
   }
  
}

// LIENZO ROTAR
void efecto3(int speed, int type_colorTransition) {
  
  //inicialization of variables
  uint8_t hue=0;
  uint8_t sat=0;
  uint8_t val=0;
  unsigned long effectTimer=millis();
  double countSin=0;
  float value_colorTransition = 0;
  
  //cleans the canvas
  borrar();
  
  //serial function parameters
  Serial.println("EFECTO LIENZO ROTAR: ");
  Serial.print(speed);
  Serial.print(" ");
  Serial.print(type_colorTransition);

  //initializes the matrix
  for (int n=0; n<400; n++) {
    lienzoHSV2[n][0]=0;
    lienzoHSV2[n][1]=lienzoHSV[n][1];
    lienzoHSV2[n][2]=lienzoHSV[n][2];
  }
  
  //efect loop
  while (efectoIdx==3) {
    //actualizes H S V for every led
    for (int y=0; y<20; y++) {
      for (int x=0; x<20; x++) {
        int l=getBufferIndex(x, y);
        hue=getLienzoH2(x,y);
        sat=getLienzoS2(x,y);
        val=getLienzoV2(x,y);
        updatePixel(l, hue, sat, val);
      }
   }

  //timer for the color transition
  if (millis()-effectTimer > speed) { //10000
    countSin = countSin + 0.05;
    effectTimer=millis();
  }
  
  //drives the type of colorTransistor
  switch (type_colorTransition)
  {
  case 1:
    value_colorTransition = abs(sin(countSin));
    break;
  case 2:
    value_colorTransition = abs(sin(sqrt(countSin)));
    break;
  case 3:
    value_colorTransition = abs(sin(tan(countSin)));
    break;  
  default:
    value_colorTransition = 1;
    break;
  }  


  for (int n=0; n<400; n++) {
    uint8_t hueLienzo = lienzoHSV2[n][0];
    hueLienzo++;
    if(hueLienzo == 255)
    {
      hueLienzo = 0;
    }
    lienzoHSV2[n][0] = hueLienzo;
    }
  Serial.println(value_colorTransition);
  delay ((sp*10*value_colorTransition)+5);
  serialCheck();
  }
}

