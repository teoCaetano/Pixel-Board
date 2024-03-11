#include <Arduino.h>
#include <FastLED.h>
#include "efecto_1.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classArco.h"
#include "classFrame.h"
#include "classAlma.h"
#include "FastNoiseLite.h"

void efecto1()
{

    int ranSeed = random(0,2000);
    alma1.setAlmaTo(alma1.saturationEffecto, 250);
    alma1.setAlmaTo(alma1.valueEffecto, 250);
    alma1.setNoiseWarpSeed(500);


    unsigned int reloj = 0;
    int hue = 0;
    float sumFloat = 0.1;
    bool flagHue = false;

    // efect loop
    while (Efecto == EFECTO1)
    {
        if (millis() > reloj + 100)
        {
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
            reloj = millis();
        }
        noise.SetFrequency(0.9f);
        noise2.SetFrequency(0.9f);

        alma1.setAlmaTo(alma1.hueEffecto, hue);
        alma1.setNoiseWarp(FastNoiseLite::DomainWarpType_BasicGrid, sumFloat, 0);
        alma1.setAlmaNoiseTo(noise, alma1.valueNoise, 250);
        alma1.setAlmaNoiseTo(noise2, alma1.saturationNoise, 250);
        algoo.clearBuffer();
        alma1.writeToFrame();
        algoo.updateFrameBuffer(frameBuffer);
        serialCheck();
    }
}