#include <Arduino.h>
#include <FastLED.h>
#include "efecto_7.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classTransition_1.h"
#include "classArco.h"
#include "classFrame.h"
#include "classAlma.h"
#include "FastNoiseLite.h"

// LIENZO ROTAR
void efecto7()
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

    float inputSeno = 0;
    float valueSeno = 0;

    // efect loop
    while (Efecto == EFECTO7)
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
        inputSeno = inputSeno + 0.008;
        if (millis() > relojTransicion1 + 30)
        {
            valueSeno = sin(inputSeno) * sin(inputSeno * 1.2);
            valueSeno = valueSeno + 1;
            valueSeno = valueSeno * 2;
            Serial.println(int(valueSeno));

            transit.showFillallIn(int(valueSeno));
            relojTransicion1 = millis();
        }

        noise.SetFrequency(1.1f);
        noise2.SetFrequency(1.9f);

        alma1.setNoiseWarp(FastNoiseLite::DomainWarpType_BasicGrid, sumFloat, 0);
        alma1.setAlmaNoiseTo(noise, alma1.valueNoise, 30);
        alma1.setAlmaNoiseTo(noise2, alma1.saturationNoise, 10);
        algoo.clearBuffer();
        alma1.writeToFrame();
        algoo.updateFrameBuffer(frameBuffer);
        alma1.setBufferAmplitud(sumFloat);
        serialCheck();
    }
}