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
  classArco arco3(algoo);
  arco3.setAngluoInValues(45, 90);
  classArco arco4(algoo);
  arco4.setAngluoInValues(90, 135);
  classArco arco5(algoo);
  arco5.setAngluoInValues(135, 180);
  unsigned int reloj = 0;
  int hue = 0;
  int suma1 = 1;
  int suma2 = 2;
  int suma3 = 3;
  // efect loop
  while (true)
  {
    if (millis() > reloj + 30)
    {
      reloj = millis();
      // hue++;
      hue = hue + 2;
      if (hue > 255)
      {
        hue = 0;
      }
      arco2.desplazoAngulo(2);
      arco3.desplazoAngulo(3);
      arco4.desplazoAngulo(4);
      arco5.desplazoAngulo(5);
      // arco2.aumentoAngulo(1);
      // arco1.desplazoAngulo(3);
      // arco1.aumentoAngulo(1);
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
    // efecto 4
    /*
    arco1.setArcoFade(algoo, arco1.hueEffecto, 0, 255);
    arco1.setArcoRingsFade(algoo, arco1.saturationEffecto, 250, 0);
    arco1.setArcoRingsFade(algoo, arco1.valueEffecto, 0, 255);
    */
    // efecto 5
    /*
    arco1.setArcoTo(algoo, arco1.hueEffecto, hue);
    arco1.setArcoRingsFade(algoo, arco1.saturationEffecto, 250, 80);
    arco1.setArcoRingsFade(algoo, arco1.valueEffecto, 0, 255);

    arco2.setArcoTo(algoo, arco2.saturationEffecto,200);
    */
    // efecto 6
    /*
    arco1.setArcoFade(algoo, arco1.hueEffecto, 0, 255);
    arco1.setArcoRingsFade(algoo, arco1.saturationEffecto, 250, 0);
    arco1.setArcoRingsFade(algoo, arco1.valueEffecto, 0, 255);
    arco2.setArcoFade(algoo, arco2.saturationEffecto,100,200);
    */
    // efecto 8
    /*
    arco1.setArcoFade(algoo, arco1.hueEffecto, 0, 255);
    arco1.setArcoRingsFade(algoo, arco1.saturationEffecto, 250, 0);
    arco1.setArcoRingsFade(algoo, arco1.valueEffecto, 0, 255);
    arco2.setArcoFade(algoo, arco2.saturationEffecto, 100, 200);
    arco2.removeRing(algoo, 8);
    arco2.removeRing(algoo, 7);
    arco2.removeRing(algoo, 6);
    arco2.removeRing(algoo, 5);
    arco2.removeRing(algoo, 4);
    arco3.setArcoFade(algoo, arco3.saturationEffecto, 100, 200);
    arco3.removeRing(algoo, 10);
    arco3.removeRing(algoo, 7);
    arco3.removeRing(algoo, 6);
    arco3.removeRing(algoo, 5);
    arco3.removeRing(algoo, 4);
    arco4.setArcoFade(algoo, arco4.saturationEffecto, 100, 200);
    arco4.removeRing(algoo, 10);
    arco4.removeRing(algoo, 9);
    arco4.removeRing(algoo, 6);
    arco4.removeRing(algoo, 5);
    arco4.removeRing(algoo, 4);
    */
    // efecto 9
    /*
    arco1.setArcoFade(algoo, arco1.hueEffecto, 0, 255);
    arco1.setArcoRingsFade(algoo, arco1.saturationEffecto, 250, 0);
    //arco1.setArcoRingsFade(algoo, arco1.valueEffecto, 0, 255);
    arco2.setArcoFade(algoo, arco2.saturationEffecto, 100, 200);
    arco2.setArcoTo(algoo, arco2.valueEffecto,255);
    arco2.removeRing(algoo, 10);
    arco3.setArcoFade(algoo, arco3.saturationEffecto, 100, 200);
    arco3.setArcoTo(algoo, arco3.valueEffecto,255);
    arco3.removeRing(algoo, 10);
    arco3.removeRing(algoo, 9);

    arco4.setArcoFade(algoo, arco4.saturationEffecto, 100, 200);
    arco4.setArcoTo(algoo, arco4.valueEffecto,255);
    arco4.removeRing(algoo, 10);
    arco4.removeRing(algoo, 9);
    arco4.removeRing(algoo, 8);

    arco5.setArcoFade(algoo, arco5.saturationEffecto, 100, 200);
    arco5.setArcoTo(algoo, arco5.valueEffecto,255);
    arco5.removeRing(algoo, 10);
    arco5.removeRing(algoo, 9);
    arco5.removeRing(algoo, 8);
    arco5.removeRing(algoo, 7);
    */

    algoo.clearBuffer();
    arco1.writeToFrame(algoo);
    arco2.writeToFrame(algoo);
    arco3.writeToFrame(algoo);
    arco4.writeToFrame(algoo);
    arco5.writeToFrame(algoo);
    algoo.updateFrameBuffer(frameBuffer);
    serialCheck();
  }
}
