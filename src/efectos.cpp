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
void efecto3() {
  //SACAR LO QUE DA MARRON
  uint8_t hue=0;
  uint8_t sat=0;
  uint8_t val=0;
  unsigned long effectTimer=millis();
  double countSin=0;
  borrar();
  Serial.println("EFECTO 3"); 

  for (int n=0; n<400; n++) {
    lienzoHSV2[n][0]=0;
    lienzoHSV2[n][1]=lienzoHSV[n][1];
    lienzoHSV2[n][2]=lienzoHSV[n][2];
  }
  while (efectoIdx==3) {
    for (int y=0; y<20; y++) {
      for (int x=0; x<20; x++) {
        int l=getBufferIndex(x, y);
        hue=getLienzoH2(x,y);
        sat=getLienzoS2(x,y);
        val=getLienzoV2(x,y);
        if (val > 180)
          val=180;
        updatePixel(l, hue, sat, val);
      }
   }
  
  //FastLED.show();
  if (millis()-effectTimer > 100) { //10000
    countSin = countSin + 0.08;
    effectTimer=millis();
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
  Serial.println(abs(sin(countSin)));
  delay ((100*abs(sin(countSin)))+5);
  serialCheck();
  }
}

