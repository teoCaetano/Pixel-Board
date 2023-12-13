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
void efecto3(bool enable_colorTransition, int speed_colorTransition, int type_colorTransition, bool absolut_colorTransition ,bool enable_brightnessTransition , int speed_brightnessTransition, int type_brightnessTransition, bool absolut_brightnessTransition) {
  
  //inicialization of variables
  uint8_t hue=0;
  uint8_t sat=0;
  uint8_t val=0;
  unsigned long timer_colorTransition=millis();
  unsigned long timer_brightnessTransition=millis();
  double count_colorTransition = 0;
  double count_brightnessTransition = 0;
  float value_colorTransition = 0;
  float value_brightnessTransition = 0;
  
  //cleans the canvas
  borrar();
  
  //serial function parameters
  Serial.println("EFECTO LIENZO ROTAR: ");
  Serial.print(speed_colorTransition);
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

  //---------------------------------------------------------------------------------------------------------
  //color transition code
  //---------------------------------------------------------------------------------------------------------

  //timer for the color transition
  if (enable_colorTransition == true)
  {
  if (millis()-timer_colorTransition > speed_colorTransition) { //10000
    count_colorTransition = count_colorTransition + 0.05;
    timer_colorTransition=millis();
  }

  //drives the type of colorTransistor
  switch (type_colorTransition)
  {
  case 1:
    value_colorTransition = sin(count_colorTransition);
    break;
  case 2:
    value_colorTransition = sin(sqrt(count_colorTransition));
    break;
  case 3:
    value_colorTransition = sin(tan(count_colorTransition));
    break;
  case 4:
    value_colorTransition = (sin(count_colorTransition)/3) + 0.5;
    break;    
  default:
    value_colorTransition = 1;
    break;
  }
  //defines if the color trasition is te absolute or just the positives
  if (absolut_colorTransition == true)
  {
    value_colorTransition = abs(value_colorTransition);
  }
  if (absolut_colorTransition == false)
  {
    if (value_colorTransition < 0)
    {
      value_colorTransition = 0;
    }
  }
  }
  if (enable_colorTransition == false)
  {
    value_colorTransition = 1;
    sp = 3;
  }
  

  //---------------------------------------------------------------------------------------------------------
  //brightness transition code
  //---------------------------------------------------------------------------------------------------------
  
  if (enable_brightnessTransition == true)
  {
  if (millis()-timer_brightnessTransition > speed_brightnessTransition) { //10000
    count_brightnessTransition = count_brightnessTransition + 0.05;
    timer_brightnessTransition=millis();
  }  

  switch (type_brightnessTransition)
  {
  case 1:
    value_brightnessTransition = sin(count_brightnessTransition);
    break;
  case 2: //esta no
    value_brightnessTransition = sin(sqrt(count_brightnessTransition));
    break;
  case 3:
    value_brightnessTransition = sin(tan(count_brightnessTransition));
    break;
  case 4:
    value_brightnessTransition = (sin(count_brightnessTransition)/3) + 0.3;
    break;    
  default:
    value_brightnessTransition = 1;
    break;
  }
  //defines if the color trasition is te absolute or just the positives
  if (absolut_brightnessTransition == true)
  {
    value_brightnessTransition = abs(value_brightnessTransition);
  }
  if (absolut_brightnessTransition == false)
  {
    if (value_brightnessTransition < 0)
    {
      value_brightnessTransition = 0;
    }
  }
  if (value_brightnessTransition<0.1)
  {
    value_brightnessTransition = 0.1;
  }
  
  newBr = int(BRIGHTNESS*value_brightnessTransition);
  Serial.println(newBr);    
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
  delay ((sp*10*value_colorTransition)+10);
  serialCheck();
  }
}

