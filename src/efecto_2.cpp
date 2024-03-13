#include <Arduino.h>
#include <FastLED.h>
#include "efecto_2.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classTransition_1.h"
#include "classArco.h"
#include "classFrame.h"
#include "classAlma.h"
#include "FastNoiseLite.h"

// LIENZO ROTAR
void efecto2()
{

    initEfectos();
    alma1.setAlmaTo(alma1.hueEffecto, alma1.getBufferHue());

    classTransition1 transit(algoo, alma1);

    unsigned int relojNoise = millis();
    unsigned int relojTransicion1 = millis();

    int frame = 1;
    int subFrame = 0;

    bool flagFloat = false;
    float sumFloat = alma1.getBufferAmplitud();

    bool flagEfecto2 = false;

    // efect loop
    while (Efecto == EFECTO2)
    {
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

        if (millis() > relojTransicion1 + 40)
        {
            if (frame <= 10)
            {
                transit.showFillallIn(frame);
            }
            if (frame > 10)
            {
                flagEfecto2 = true;
                Efecto = EFECTO3;
            }
            if (frame < 0)
            {
                flagEfecto2 = false;
            }

            if (subFrame < 10)
            {
                if (flagEfecto2 == false)
                {
                    subFrame++;
                }
                if (flagEfecto2 == true)
                {
                    subFrame--;
                }
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

        alma1.setNoiseWarp(FastNoiseLite::DomainWarpType_BasicGrid, sumFloat, 0);
        alma1.setAlmaNoiseTo(noise, alma1.valueNoise, 30);
        alma1.setAlmaNoiseTo(noise2, alma1.saturationNoise, 30);
        algoo.clearBuffer();
        alma1.writeToFrame();
        algoo.updateFrameBuffer(frameBuffer);
        alma1.setBufferAmplitud(sumFloat);
        serialCheck();
    }
}