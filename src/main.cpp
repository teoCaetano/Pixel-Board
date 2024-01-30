#include <Arduino.h>
#include <FastLED.h>
#include "config.h"
#include "efectos.h"
#include "graphics.h"
#include "main.h"
#include "frame.h"
#include "classFrame.h"

int br = BRIGHTNESS;
int newBr = br;
int sp = 9;

CRGB leds[NUM_LEDS];
uint8_t frameBuffer[FRAME_BUFFER_SIZE][3];

int bufferToPixeledBase(int x, int y)
{
  int index = y * WIDTH + x;
  return frame2PixelLedMap[index];
}

int getLienzoH(int x, int y)
{
  int index = y * WIDTH + x;
  return lienzoHSV[index][0];
}
int getLienzoS(int x, int y)
{
  int index = y * WIDTH + x;
  return lienzoHSV[index][1];
}
int getLienzoV(int x, int y)
{
  int index = y * WIDTH + x;
  return lienzoHSV[index][2];
}

int getLienzoH2(int x, int y)
{
  int index = y * WIDTH + x;
  return lienzoHSV2[index][0];
}
int getLienzoS2(int x, int y)
{
  int index = y * WIDTH + x;
  return lienzoHSV2[index][1];
}
int getLienzoV2(int x, int y)
{
  int index = y * WIDTH + x;
  return lienzoHSV2[index][2];
}

void setup()
{
  Serial.begin(115200);
  classFrame algoo(HEIGHT,WIDTH);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  cartesianConstructor();
  poolarConstructor(0,0);
  matrixConstructor(SERPENTY, START_LOCATION, SYMETRIC, 1, ROUND_MATRIX);
  hueConstructor(hueMin, hueMax);
  poolarConstructor(0,0);
  int valorMax = algoo.getMaxRadio();
  algoo.fill_pixelsPerRadio();
  saturacionConstructor(valorMax);
  valueConstructor(valorMax);
  FastLED.setBrightness(br);
  FastLED.clear();
  FastLED.show(); // display this frame
  delay(200);
  clearFrameBuffer();

  xTaskCreatePinnedToCore(
      updateLedsTask,   /* Function to implement the task */
      "updateLedsTask", /* Name of the task */
      10000,            /* Stack size in words */
      NULL,             /* Task input parameter */
      0,                /* Priority of the task */
      NULL,             /* Task handle. */
      0);               /* Core where the task should run */
  Serial.println("START!");
}

void loop()
{
  efecto3();
}

void serialCheck()
{
  if (Serial.available())
  {
    char ch = Serial.read();
    Serial.println(ch);
    if (ch == '+')
      subirSpeed();
    else if (ch == '-')
      bajarSpeed();
    else if (ch == 'q')
      subirBrillo();
    else if (ch == 'a')
      bajarBrillo();
  }
}

void subirSpeed()
{
  sp -= 1;
  if (sp < 0)
    sp = 0;
  Serial.print("SP: ");
  Serial.println(sp);
}
void bajarSpeed()
{
  sp += 1;
  if (sp > 10)
    sp = 10;
  Serial.print("SP: ");
  Serial.println(sp);
}

void subirBrillo()
{
  int b = newBr + 10;
  if (b > BRIGHTNESS)
    b = BRIGHTNESS;
  newBr = b;
}

void bajarBrillo()
{
  int b = newBr - 10;
  if (b < 10)
    b = 10;
  newBr = b;
}


