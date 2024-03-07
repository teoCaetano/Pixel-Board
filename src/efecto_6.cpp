#include <Arduino.h>
#include <FastLED.h>
#include "efecto_6.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classTransition_1.h"
#include "classArco.h"
#include "classFrame.h"
#include "classAlma.h"
#include "FastNoiseLite.h"

// LIENZO ROTAR
void efecto6()
{

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

    alma1.setAlmaTo(alma1.hueEffecto, alma1.getBufferHue());

    classTransition1 transit(algoo, alma1);

    unsigned int relojNoise = millis();
    unsigned int relojTransicion1 = millis();

    int frame = 1;
    int subFrame = 0;

    bool flagFloat = false;
    float sumFloat = alma1.getBufferAmplitud();

    bool flagEfecto2 = false;

    float inputSeno = 0;
    float valueSeno = 0;

    // efect loop
    while (Efecto == EFECTO6)
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

        if (millis() > relojTransicion1 + 80)
        {
            subFrame++;
            inputSeno = inputSeno + 0.1;
            if (subFrame == 10)
            {
                subFrame = 0;
                valueSeno = sin(inputSeno);
                valueSeno = valueSeno + 1;
                valueSeno = valueSeno * 3;
                valueSeno = valueSeno -1;
            }
            transit.showFillallIn(int(valueSeno));
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