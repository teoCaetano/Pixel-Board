#include <Arduino.h>
#include <FastLED.h>
#include "efectos.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classTransition.h"

 uint8_t lienzoHue[FRAME_BUFFER_SIZE];
 uint8_t lienzoSaturacion[FRAME_BUFFER_SIZE];
 uint8_t lienzoValue[FRAME_BUFFER_SIZE];

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

  // inicialization of variables
  uint8_t hue = 0;
  uint8_t sat = 0;
  uint8_t val = 0;
  int delay_Transition = 0;
  int amplitud_Transition = sp * 10;
  int sentido = 0;
  unsigned long timer_Transition = millis();
  float value_colorTransition = 0;
  float value_brightnessTransition = 0;
  classTransition color(50, 0, true);
  classTransition brightness(100, 0, true);
  classTransition flow(100, 0, true);

  // efect loop
  while (true)
  {
    // actualizes H S V for every led
    for (int i = 0; i < FRAME_BUFFER_SIZE; i++)
    {
      updatePixel(i, lienzoHue[i], lienzoSaturacion[i], lienzoValue[i]);
    }
    
    //---------------------------------------------------------------------------------------------------------
    // color transition code
    //---------------------------------------------------------------------------------------------------------
    value_colorTransition = color.methodValue();
    amplitud_Transition = sp * 10;
    delay_Transition = amplitud_Transition * value_colorTransition + 10;
    //---------------------------------------------------------------------------------------------------------
    // brightness transition code
    //---------------------------------------------------------------------------------------------------------
    value_brightnessTransition = brightness.methodValue();
    newBr = int(BRIGHTNESS * value_brightnessTransition);
    //---------------------------------------------------------------------------------------------------------
    // sentido transition code
    //---------------------------------------------------------------------------------------------------------
    sentido = 100 * flow.methodValue();

    if (millis() - timer_Transition > delay_Transition)
    {
      for (int n = 0; n < FRAME_BUFFER_SIZE; n++)
      {
        uint8_t hueLienzo = lienzoHue[n];
        if (sentido < 70)
        {
          hueLienzo++;
          if (hueLienzo >= hueMax)
          {
            hueLienzo = hueMin;
          }
        }
        else
        {
          hueLienzo--;
          if (hueLienzo <= hueMin)
          {
            hueLienzo = hueMax;
          }
        }

        lienzoHue[n] = hueLienzo;
      }
      timer_Transition = millis();
    }
    serialCheck();
  }
}
