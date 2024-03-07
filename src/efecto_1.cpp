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

    alma1.setAlmaRingTo(alma1.valueEffecto, 10, 150);
    alma1.setAlmaRingTo(alma1.valueEffecto, 9, 100);
    alma1.setAlmaRingTo(alma1.valueEffecto, 8, 50);
    alma1.setAlmaRingTo(alma1.valueEffecto, 7, 0);
    alma1.setAlmaRingTo(alma1.valueEffecto, 6, 0);
    alma1.setAlmaRingTo(alma1.valueEffecto, 5, 0);
    alma1.setAlmaRingTo(alma1.valueEffecto, 4, 0);
    alma1.setAlmaRingTo(alma1.valueEffecto, 3, 0);
    alma1.setAlmaRingTo(alma1.valueEffecto, 2, 0);
    alma1.setAlmaRingTo(alma1.valueEffecto, 1, 0);

    alma1.setAlmaRingTo(alma1.saturationEffecto, 10, 200);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 9, 200);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 8, 200);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 7, 200);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 6, 200);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 5, 200);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 4, 200);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 3, 200);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 2, 200);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 1, 200);

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
        noise.SetFrequency(0.5f);
        noise2.SetFrequency(0.5f);

        alma1.setAlmaTo(alma1.hueEffecto, hue);
        alma1.setNoiseWarp(FastNoiseLite::DomainWarpType_BasicGrid, sumFloat, 0);
        alma1.setAlmaNoiseTo(noise, alma1.valueNoise, 250);
        alma1.setAlmaNoiseTo(noise2, alma1.saturationNoise, 30);
        algoo.clearBuffer();
        alma1.writeToFrame();
        algoo.updateFrameBuffer(frameBuffer);
        serialCheck();
    }
}