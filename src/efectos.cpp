#include <Arduino.h>
#include <FastLED.h>
#include "efectos.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classTransition.h"
#include "classArco.h"
#include "classFrame.h"

void updatePixel(int pixel, int hue, int sat, int val)
{
  if (val < 0)
    val = 0;
  else if (val > 255)
    val = 255;
  if (pixel >= 0 && pixel < FRAME_BUFFER_SIZE)
  {
    frameBuffer[pixel][0] = hue;
    frameBuffer[pixel][1] = sat;
    frameBuffer[pixel][2] = val;
  }
}

// LIENZO ROTAR
void efecto3()
{
  classArco arco1(algoo);
  arco1.setAngluoInValues(0, 359);
  classArco arco2(algoo);
  arco2.setAngluoInValues(0, 45);
  unsigned int reloj = 0;
  int hue = 0;
  // efect loop
  while (true)
  {
    if (millis() > reloj + 30)
    {
      reloj = millis();
      //hue++;
      hue = hue +2 ;
      if (hue > 255)
      {
        hue = 0;
      }
        arco2.desplazoAngulo(2);
        //arco2.aumentoAngulo(1);
        arco1.desplazoAngulo(1);
      //arco1.aumentoAngulo(1);
    }
    // efecto 1
    /*
      arco1.setArcoFade(algoo, arco1.hueEffecto, 0, 255);
      arco1.setArcoFade(algoo, arco1.saturationEffecto, 255, 0);
      arco1.setArcoRingsFade(algoo, arco1.valueEffecto, 0, 255);
    */
    // efecto 2

    /*
      arco1.setArcoFade(algoo, arco1.hueEffecto, 0, 255);
      arco1.setArcoRingsFade(algoo, arco1.saturationEffecto, 250, hue);
      arco1.setArcoRingsFade(algoo, arco1.valueEffecto, 0, 255);
    */
    // efecto 3

    /*
      arco1.setArcoFade(algoo, arco1.hueEffecto, 125, 150);
      arco1.setArcoFade(algoo, arco1.valueEffecto, 255, 0);
      arco1.setArcoRingsFade(algoo, arco1.saturationEffecto, 0, 250);
    */
    //efecto 4
    /*
    arco1.setArcoFade(algoo, arco1.hueEffecto, 0, 255);
    arco1.setArcoRingsFade(algoo, arco1.saturationEffecto, 250, 0);
    arco1.setArcoRingsFade(algoo, arco1.valueEffecto, 0, 255);
    */
    //efecto 5
    /*
    arco1.setArcoTo(algoo, arco1.hueEffecto, hue);
    arco1.setArcoRingsFade(algoo, arco1.saturationEffecto, 250, 80);
    arco1.setArcoRingsFade(algoo, arco1.valueEffecto, 0, 255);

    arco2.setArcoTo(algoo, arco2.saturationEffecto,200);   
    */
    arco1.setArcoFade(algoo, arco1.hueEffecto, 0, 255);
    arco1.setArcoRingsFade(algoo, arco1.saturationEffecto, 250, 0);
    arco1.setArcoRingsFade(algoo, arco1.valueEffecto, 0, 255);
    arco2.setArcoFade(algoo, arco2.saturationEffecto,100,200);   

    algoo.clearBuffer();
    arco1.writeToFrame(algoo);
    arco2.writeToFrame(algoo);
    algoo.updateFrameBuffer(frameBuffer);
    serialCheck();
  }
}
