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
  unsigned int reloj = 0;
  int angulooo = 90;
  int anguloooMin = 0;
  int hue = 0;
  // efect loop
  while (true)
  {
    if (millis() > reloj + 30)
    {
      angulooo++;
      anguloooMin++;
      reloj = millis();
      if (angulooo > 360)
      {
        hue = hue + 15;
        angulooo = 0;
      }
      if (anguloooMin > 360)
      {
        anguloooMin = 0;
      }
      if (hue > 255)
      {
        hue = 0;
      }
    }
    arco1.setAngluoInValues(angulooo, anguloooMin);
    arco1.setArcoHue(algoo, hue);
    arco1.setArcoSat(algoo, 200);
    arco1.setArcoVal(algoo, 200);
    algoo.clearBuffer();
    arco1.writeToFrame(algoo);
    algoo.updateFrameBuffer(frameBuffer);
    serialCheck();
  }
}
