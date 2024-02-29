#include "graphics.h"
#include "config.h"
#include "main.h"

void scaleInSteps(int &value, int from, int to, int steps)
{
  int absolut_restToVal;
  int restToVal = to - value;

  int absolut_pieceOfRange;
  int range = to - from;
  int pieceOfRange;

  // this part checks if value is in the range of FROM and TO and
  bool enableFunction = ((value >= from) && (value < to)) || ((value <= from) && (value > to));
  bool restoRange = ((range % steps) == 0);
  if (from == to)
  {
    enableFunction = false;
  }

  if (enableFunction && restoRange)
  {
    pieceOfRange = range / steps;
    value = value + pieceOfRange;
  }
  if (enableFunction && !restoRange)
  {
    pieceOfRange = range / (steps - 1);
    absolut_pieceOfRange = abs(pieceOfRange);
    absolut_restToVal = abs(restToVal);
    if (absolut_restToVal < absolut_pieceOfRange)
    {
      value = value + restToVal;
    }
    else
    {
      value = value + pieceOfRange;
    }
  }
}

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

void clearFrameBuffer()
{
  for (int n = 0; n < FRAME_BUFFER_SIZE; n++)
  {
    frameBuffer[n][0] = 0;
    frameBuffer[n][1] = 0;
    frameBuffer[n][2] = 0;
  }
}

void updateLedsTask(void *pvParameters)
{
  Serial.print("STARTING VIDEO TASK ON CORE: ");
  Serial.println(xPortGetCoreID());
  while (1)
  {
    updateLeds();
  }
}

void updateLedsSerial()
{
  for (int n = 0; n < FRAME_BUFFER_SIZE; n++)
  {
    int pixelLed = frame2PixelLedMap[n];
    if (pixelLed > -1)
    {
      uint8_t h = frameBuffer[n][0];
      uint8_t s = frameBuffer[n][1];
      uint8_t v = frameBuffer[n][2];
      leds[pixelLed] = CHSV(h, s, v);
      leds[pixelLed + 1] = CHSV(h, s, v);
      leds[pixelLed + 2] = CHSV(h, s, v);
      Serial.printf("%d,%d,%d;", leds[pixelLed].r, leds[pixelLed].g, leds[pixelLed].b);
    }
    else
      Serial.print("0,0,0;");
  }
  Serial.println();
}

void updateLeds()
{
  for (int n = 0; n < FRAME_BUFFER_SIZE; n++)
  {
    int pixelLed = frame2PixelLedMap[n];
    int ledsPerPixel = ledsPerPixel_prueba[n];
    if (pixelLed > -1)
    {
      uint8_t h = frameBuffer[n][0];
      uint8_t s = frameBuffer[n][1];
      uint8_t v = frameBuffer[n][2];
      for (int i = 0; i < ledsPerPixel; i++)
      {
        leds[pixelLed + i] = CHSV(h, s, v);
      }
    }
  }
  if (newBr != br)
  {
    br = newBr;
    FastLED.setBrightness(br);
  }
  FastLED.show();
}
