#include <Arduino.h>
#include <FastLED.h>
#include "config.h"
#include "Debug_tools.h"
#include "efecto_1.h"
#include "efecto_2.h"
#include "efecto_3.h"
#include "efecto_4.h"
#include "efecto_5.h"
#include "efecto_6.h"
#include "efecto_7.h"
#include "efecto_8.h"
#include "graphics.h"
#include "main.h"
#include "classFrame.h"
#include "FastNoiseLite.h"

int br = BRIGHTNESS;
int newBr = br;
int sp = 9;

CRGB leds[NUM_LEDS];
uint8_t frameBuffer[FRAME_BUFFER_SIZE][3];
int frame2PixelLedMap[FRAME_BUFFER_SIZE];
int ledsPerPixel_prueba[FRAME_BUFFER_SIZE];

classFrame algoo(HEIGHT, WIDTH);
classAlma alma1(algoo);

FastNoiseLite noise;

FastNoiseLite noise2;

enum Efectos Efecto = NINGUNO;

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
  noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
  noise2.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
  noise2.SetSeed(1231);
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
  switch (Efecto)
  {
  case NINGUNO:
    Serial.println("DEBUG");
    DebugFrame();
    break;
  case EFECTO1:
    Serial.println("efecto 1");
    efecto1();
    break;
  case EFECTO2:
    Serial.println("efecto 2");
    efecto2();
    break;
  case EFECTO3:
    Serial.println("efecto 3");
    efecto3();
    break;
  case EFECTO4:
    Serial.println("efecto 4");
    efecto4();
  case EFECTO5:
    Serial.println("efecto 5");
    efecto5();
  case EFECTO6:
    Serial.println("efecto 6");
    efecto6();
  case EFECTO7:
    Serial.println("efecto 7");
    efecto7();
  case EFECTO8:
    Serial.println("efecto 8");
    efecto8();
    break;
  default:
    break;
  }
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
    else if (ch == '1')
      Efecto = EFECTO1;
    else if (ch == '2')
      Efecto = EFECTO2;
    else if (ch == '3')
      Efecto = EFECTO3;
    else if (ch == '4')
      Efecto = EFECTO4;
    else if (ch == '5')
      Efecto = EFECTO5;
    else if (ch == '6')
      Efecto = EFECTO6;
    else if (ch == '7')
      Efecto = EFECTO7;
    else if (ch == '8')
      Efecto = EFECTO8;
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
