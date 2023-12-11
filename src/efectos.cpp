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
  int sat=0;
  int val=0;
  unsigned long effectTimer=millis();
  int count=0;
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
  if (millis()-effectTimer > 10000) { //10000
    effectTimer=millis();
    count++;
    if (count>=10)
      count=0;
      
    Serial.println(count);
  }
  for (int n=0; n<400; n++) {
    int h=lienzoHSV2[n][0];
    int b=count * 20; //20
    if (count == 0) {
      lienzoHSV2[n][0]++;
    }
    else if (h<b || h > b+10)
      lienzoHSV2[n][0]++;
    }
  delay (sp*10);
  serialCheck();

  }
}

