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

    alma1.setAlmaTo(alma1.saturationEffecto, 250);
    alma1.setAlmaTo(alma1.valueEffecto, 250);

    alma1.setAlmaRingTo(alma1.valueEffecto, 10, 255);
    alma1.setAlmaRingTo(alma1.valueEffecto, 9, 250);
    alma1.setAlmaRingTo(alma1.valueEffecto, 8, 245);
    alma1.setAlmaRingTo(alma1.valueEffecto, 7, 225);
    alma1.setAlmaRingTo(alma1.valueEffecto, 6, 200);
    alma1.setAlmaRingTo(alma1.valueEffecto, 5, 140);
    alma1.setAlmaRingTo(alma1.valueEffecto, 4, 100);
    alma1.setAlmaRingTo(alma1.valueEffecto, 3, 50);
    alma1.setAlmaRingTo(alma1.valueEffecto, 2, 10);
    alma1.setAlmaRingTo(alma1.valueEffecto, 1, 0);

    alma1.setAlmaRingTo(alma1.saturationEffecto, 10, 25);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 9, 45);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 8, 65);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 7, 100);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 6, 140);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 5, 200);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 4, 215);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 3, 180);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 2, 180);
    alma1.setAlmaRingTo(alma1.saturationEffecto, 1, 0);

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
        if (millis() > relojTimeStop + 10000)
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
