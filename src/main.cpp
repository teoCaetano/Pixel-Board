#include <Arduino.h>
#include <FastLED.h>
#include "config.h"
#include "efectos.h"
#include "graphics.h"
#include "main.h"
#include "classFrame.h"

int br = BRIGHTNESS;
int newBr = br;
int sp = 9;

CRGB leds[NUM_LEDS];
uint8_t frameBuffer[FRAME_BUFFER_SIZE][3];
int frame2PixelLedMap[FRAME_BUFFER_SIZE];
int ledsPerPixel_prueba[FRAME_BUFFER_SIZE];

classFrame algoo(HEIGHT,WIDTH);

void setup()
{
  Serial.begin(115200);
  algoo.constructorXY();
  algoo.constructorPolar();
  algoo.constructorMapDegre();
  algoo.matrixConstructor(SERPENTY, START_LOCATION, SYMETRIC, 3, ROUND_MATRIX);
  algoo.writeLedsPerPixelsTo(ledsPerPixel_prueba);
  algoo.writepixelLedMapTo(frame2PixelLedMap);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
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


