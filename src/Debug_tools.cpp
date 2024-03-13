#include <Arduino.h>
#include <FastLED.h>
#include "Debug_tools.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "classArco.h"
#include "classFrame.h"
#include "classAlma.h"
#include "FastNoiseLite.h"

void DebugFrame()
{
    while (Efecto == NINGUNO)
    {
        clearFrameBuffer();
        for (int i = 0; i < 400; i++)
        {
            if (frame2PixelLedMap[i]>-1)
            {
                updatePixel(i, 0, 250, 250);
                Serial.println(frame2PixelLedMap[i]);
                delay(1000);
            }
            
        }
        
        serialCheck();
    }
}