#include <Arduino.h>
#include <FastLED.h>
#include "efecto_5.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classArco.h"
#include "classFrame.h"
#include "classAlma.h"
#include "FastNoiseLite.h"

// LIENZO ROTAR
void efecto5()
{
    initEfectos();

    unsigned int reloj = millis();
    unsigned int relojNoise = millis();
    unsigned int relojTimeStop = millis();

    bool flagTimeStop = true;
    bool flagHue = false;
    int hue = 0;
    int hueFuturo = 20;

    bool flagFloat = false;
    float sumFloat = 0.01;

    // efect loop
    while (Efecto == EFECTO5)
    {
        if (millis() > reloj + 100)
        {
            if (flagTimeStop == true)
            {
                hue = hue + 1;
                if (hue > 255)
                {
                    hue = 0;
                }
            }
            if (hue == hueFuturo)
            {
                flagTimeStop = false;
            }

            reloj = millis();
        }
        if (millis() > relojTimeStop + 4000)
        {
            if ((255 - hue) < 20)
            {
                hueFuturo = 20 - (255 - hue);
            }
            else
            {
                hueFuturo = hue + 20;
            }

            flagTimeStop = true;
            relojTimeStop = millis();
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
            if (sumFloat >= 2.55 && flagFloat == true)
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
        serialCheck();
    }
}
