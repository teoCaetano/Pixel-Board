#include <Arduino.h>
#include <FastLED.h>
#include "efecto_3.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classArco.h"
#include "classFrame.h"
#include "classAlma.h"
#include "FastNoiseLite.h"

// LIENZO ROTAR
void efecto3()
{

  initEfectos();

  unsigned int reloj = millis();
  unsigned int relojNoise = millis();

  bool flagFloat = false;
  float sumFloat = alma1.getBufferAmplitud();

  int hue = alma1.getBufferHue();
  bool flagHue = false;

  // efect loop
  while (Efecto == EFECTO3)
  {
    if (millis() > reloj + 100)
    {
      if (flagHue == false)
      {
        hue = hue + 1;
      }
      if (hue > 255 && flagHue == false)
      {
        hue = 0;
        flagHue = true;
      }
      if (flagHue == true)
      {
        hue -= 1;
      }
      if (hue < 0 && flagHue == true)
      {
        flagHue = false;
      }
      reloj = millis();
    }
    if (millis() > relojNoise + 100)
    {
      if (flagFloat == false)
      {
        sumFloat += 0.01;
      }
      if (sumFloat >= 2.55 && flagFloat == false)
      {
        flagFloat = true;
      }
      if (flagFloat == true)
      {
        sumFloat -= 0.01;
      }
      if (sumFloat <= 0 && flagFloat == true)
      {
        flagFloat = false;
      }
      relojNoise = millis();
    }
    noise.SetFrequency(1.1f);
    noise2.SetFrequency(1.1f);

    alma1.setAlmaTo(alma1.hueEffecto, hue);
    alma1.setNoiseWarp(FastNoiseLite::DomainWarpType_BasicGrid, sumFloat, 0);
    alma1.setAlmaNoiseTo(noise, alma1.valueNoise, 30);
    alma1.setAlmaNoiseTo(noise2, alma1.saturationNoise, 30);
    algoo.clearBuffer();
    alma1.writeToFrame();
    algoo.updateFrameBuffer(frameBuffer);
    alma1.setBufferHue(hue);
    alma1.setBufferAmplitud(sumFloat);
    serialCheck();
  }
}
