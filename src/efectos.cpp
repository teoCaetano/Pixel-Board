#include <Arduino.h>
#include <FastLED.h>
#include "efectos.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classTransition.h"
#include "classArco.h"
#include "classFrame.h"
#include "classAlma.h"
#include "FastNoiseLite.h"

// interesante implementar esta funcion como metodo de classframe para hacer corecion en pixeles individuales cuando sea necesario
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
  classAlma alma1(algoo);
  FastNoiseLite noise;
  noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

  alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 10, 255);
  alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 9, 250);
  alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 8, 245);
  alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 7, 225);
  alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 6, 200);
  alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 5, 140);
  alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 4, 100);
  alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 3, 50);
  alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 2, 10);
  alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 1, 0);

  alma1.setAlmaRingTo(algoo, alma1.saturationEffecto, 10, 25);
  alma1.setAlmaRingTo(algoo, alma1.saturationEffecto, 9, 45);
  alma1.setAlmaRingTo(algoo, alma1.saturationEffecto, 8, 65);
  alma1.setAlmaRingTo(algoo, alma1.saturationEffecto, 7, 100);
  alma1.setAlmaRingTo(algoo, alma1.saturationEffecto, 6, 140);
  alma1.setAlmaRingTo(algoo, alma1.saturationEffecto, 5, 200);
  alma1.setAlmaRingTo(algoo, alma1.saturationEffecto, 4, 215);
  alma1.setAlmaRingTo(algoo, alma1.saturationEffecto, 3, 180);
  alma1.setAlmaRingTo(algoo, alma1.saturationEffecto, 2, 180);
  alma1.setAlmaRingTo(algoo, alma1.saturationEffecto, 1, 0);
  unsigned int reloj = 0;
  int hue = 0;
  float sumFloat = 0.1;
  bool flagHue = false;
  int suma1 = 1;
  int suma2 = 2;
  int suma3 = 3;
  // efect loop
  while (true)
  {
    if (millis() > reloj + 100)
    {
      reloj = millis();
      // hue++;

      if (flagHue == false)
      {
        hue = hue + 1;
        sumFloat += 0.01;
      }

      if (hue > 255 && flagHue == false)
      {
        hue = 0;
        flagHue = true;
      }
  
      if (flagHue == true)
      {
        hue -= 1;
        sumFloat -= 0.01;
      }
      

      if (hue < 0 && flagHue == true)
      {
        flagHue = false;
      }

      alma1.desplazoAngulo(1);
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
    noise.SetFrequency(1.1f);
    noise.SetDomainWarpType(FastNoiseLite::DomainWarpType_BasicGrid);
    noise.SetDomainWarpAmp(sumFloat);

    alma1.setAlmaTo(algoo, alma1.hueEffecto, hue);

    alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 10, 255);
    alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 9, 250);
    alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 8, 245);
    alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 7, 225);
    alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 6, 200);
    alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 5, 140);
    alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 4, 100);
    alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 3, 50);
    alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 2, 10);
    alma1.setAlmaRingTo(algoo, alma1.valueEffecto, 1, 0);

    alma1.setAlmaNoiseTo(algoo, noise, alma1.valueEffecto, 20);

    algoo.clearBuffer();
    /*
    arco1.writeToFrame(algoo);
    arco2.writeToFrame(algoo);
    arco3.writeToFrame(algoo);
    arco4.writeToFrame(algoo);
    arco5.writeToFrame(algoo);
    */
    alma1.writeToFrame(algoo);
    algoo.updateFrameBuffer(frameBuffer);
    serialCheck();
  }
}
