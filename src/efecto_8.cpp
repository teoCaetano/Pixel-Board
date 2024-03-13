#include <Arduino.h>
#include <FastLED.h>
#include "efecto_8.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classArco.h"
#include "classFrame.h"
#include "classAlma.h"
#include "FastNoiseLite.h"

// LIENZO ROTAR
void efecto8()
{
    classArco arco1(algoo);
    arco1.setAngluoInValues(0, 180);
    initEfectos();

    unsigned int relojNoise = millis();
    unsigned int relojTransicion1 = millis();
    unsigned int reloj = millis();

    int hue = alma1.getBufferHue();
    float sumFloat = alma1.getBufferAmplitud();

    bool flagHue;
    bool flagFloat;

    // efect loop
    while (Efecto == EFECTO8)
    {
        if (millis() > relojTransicion1 + 20)
        {
            arco1.desplazoAngulo(1);
            relojTransicion1 = millis();
        }
        if (millis() > reloj + 100)
        {
            if (flagHue == false)
            {
                hue = hue + 1;
            }
            if (hue > 255 && flagHue == false)
            {
                hue = 0;
                flagHue = true;
            }
            if (flagHue == true)
            {
                hue -= 1;
            }
            if (hue < 0 && flagHue == true)
            {
                flagHue = false;
            }
            reloj = millis();
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
            if (sumFloat <= 0 && flagFloat == true)
            {
                flagFloat = false;
            }
            relojNoise = millis();
        }

        arco1.setArcoFade(arco1.saturationEffecto, 0, 250);
        noise.SetFrequency(1.1f);
        noise2.SetFrequency(1.1f);

        alma1.setAlmaTo(alma1.hueEffecto, hue);
        alma1.setNoiseWarp(FastNoiseLite::DomainWarpType_BasicGrid, sumFloat, 0);
        alma1.setAlmaNoiseTo(noise, alma1.valueNoise, 30);
        alma1.setAlmaNoiseTo(noise2, alma1.saturationNoise, 30);
        algoo.clearBuffer();
        alma1.writeToFrame();
        arco1.writeToFrame();
        algoo.updateFrameBuffer(frameBuffer);
        serialCheck();
    }
}