#include <Arduino.h>
#include <FastLED.h>
#include "efecto_8.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classArco.h"
#include "classFrame.h"

// LIENZO ROTAR
void efecto8()
{
    classArco arco1(algoo);
    arco1.setAngluoInValues(0, 25);

    unsigned int relojNoise = millis();
    unsigned int relojTransicion1 = millis();

    // efect loop
    while (Efecto == EFECTO8)
    {
        if (millis() > relojNoise + 100)
        {
            arco1.aumentoAngulo(10);
            relojNoise = millis();
        }
        
        arco1.setArcoTo(arco1.valueEffecto, 250);
        arco1.setArcoTo(arco1.saturationEffecto, 250);
        arco1.setArcoTo(arco1.hueEffecto, 10);

        algoo.clearBuffer();
        arco1.writeToFrame();
        algoo.updateFrameBuffer(frameBuffer);
        serialCheck();
    }
}