#include <Arduino.h>
#include <FastLED.h>
#include "efecto_2.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classTransition.h"
#include "classArco.h"
#include "classFrame.h"
#include "classAlma.h"
#include "FastNoiseLite.h"

// LIENZO ROTAR
void efecto2()
{

    classAlma alma1(algoo);
    alma1.setAlmaTo(alma1.saturationEffecto, 0);
    alma1.setAlmaTo(alma1.valueEffecto, 0);

    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);

    FastNoiseLite noise2;
    noise2.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise2.SetSeed(1231);

    classTransition transit(algoo, alma1);

    unsigned int reloj = millis();
    unsigned int relojTransicion1 = millis();
    int frame = 1;
    int subFrame = 0;
    int hue = 0;
    float sumFloat = 0.1;
    bool flagHue = false;

    // efect loop
    while (Efecto == EFECTO2)
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
        if (millis() > relojTransicion1 + 100)
        {
            if (frame <= 10)
            {
                transit.showFillallIn(frame);
            }
            if (subFrame < 10)
            {
                subFrame++;
            }
            if (subFrame == 10)
            {
                subFrame = 0;
                frame++;
            }
            relojTransicion1 = millis();
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