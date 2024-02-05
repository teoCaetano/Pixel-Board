#include <Arduino.h>
#include <FastLED.h>
#include <vector>
#include <algorithm>
#include "classFrame.h"

class classArco
{
private:
    std::vector<int> hueEffecto;
    std::vector<int> saturationEffecto;
    std::vector<int> valueEffecto;

    int frameBufferSize_ef;
    int minAng;
    int maxAng;

public:
    classArco(classFrame algo);
    void setAngluoInValues(int minA, int maxA);
    void setArcoHue(classFrame algo, int to);
    void setArcoSat(classFrame algo, int to);
    void setArcoVal(classFrame algo, int to);
    void writeToFrame(classFrame& algo);
    ~classArco();
};

classArco::classArco(classFrame algo)
{
    frameBufferSize_ef = algo.getFrameBufferSize();
    hueEffecto.resize(frameBufferSize_ef, 0);
    saturationEffecto.resize(frameBufferSize_ef, 0);
    valueEffecto.resize(frameBufferSize_ef, 0);
}

void classArco::writeToFrame(classFrame& algo)
{
    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        if (hueEffecto[i] > -1)
        {
            algo.setHueFromAdress(i, hueEffecto[i]);
        }
        if (saturationEffecto[i] > -1)
        {
            algo.setSatFromAdress(i, saturationEffecto[i]);
        }
        if (valueEffecto[i] > -1)
        {
            algo.setValFromAdress(i, valueEffecto[i]);

        }
    }
}

void classArco::setAngluoInValues(int minA, int maxA)
{
    minAng = minA;
    maxAng = maxA;
    if (minAng < 0)
    {
        minAng = 360;
    }
    if (minAng > 360)
    {
        minAng = 0;
    }
    if (maxAng < 0)
    {
        maxAng = 360;
    }
    if (maxAng > 360)
    {
        maxAng = 0;
    }
}

void classArco::setArcoHue(classFrame algo, int to)
{
    int angulo_i = 0;
    bool modo_maxmax = false;
    bool modo_maxmin = false;
    if (maxAng > minAng)
    {
        modo_maxmax = true;
        modo_maxmin = false;
    }
    if (maxAng < minAng)
    {
        modo_maxmax = false;
        modo_maxmin = true;
    }

    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        angulo_i = algo.getGradFromAdress(i);
        if (modo_maxmax == true)
        {
            if ((angulo_i < maxAng) && (angulo_i > minAng))
            {
                hueEffecto[i] = to;
            }
            else
            {
                hueEffecto[i] = -1;
            }
        }
        if (modo_maxmin == true)
        {
            if ((angulo_i < minAng) && (angulo_i > maxAng))
            {
                hueEffecto[i] = -1;
            }
            else
            {
                hueEffecto[i] = to;
            }
        }
    }
}

void classArco::setArcoSat(classFrame algo, int to)
{
    int angulo_i = 0;
    bool modo_maxmax = false;
    bool modo_maxmin = false;
    if (maxAng > minAng)
    {
        modo_maxmax = true;
        modo_maxmin = false;
    }
    if (maxAng < minAng)
    {
        modo_maxmax = false;
        modo_maxmin = true;
    }

    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        angulo_i = algo.getGradFromAdress(i);
        if (modo_maxmax == true)
        {
            if ((angulo_i < maxAng) && (angulo_i > minAng))
            {
                saturationEffecto[i] = to;
            }
            else
            {
                saturationEffecto[i] = -1;
            }
        }
        if (modo_maxmin == true)
        {
            if ((angulo_i < minAng) && (angulo_i > maxAng))
            {
                saturationEffecto[i] = -1;
            }
            else
            {
                saturationEffecto[i] = to;
            }
        }
    }
}

void classArco::setArcoVal(classFrame algo, int to)
{
    int angulo_i = 0;
    bool modo_maxmax = false;
    bool modo_maxmin = false;
    if (maxAng > minAng)
    {
        modo_maxmax = true;
        modo_maxmin = false;
    }
    if (maxAng < minAng)
    {
        modo_maxmax = false;
        modo_maxmin = true;
    }

    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        angulo_i = algo.getGradFromAdress(i);
        if (modo_maxmax == true)
        {
            if ((angulo_i < maxAng) && (angulo_i > minAng))
            {
                valueEffecto[i] = to;
            }
            else
            {
                valueEffecto[i] = -1;
            }
        }
        if (modo_maxmin == true)
        {
            if ((angulo_i < minAng) && (angulo_i > maxAng))
            {
                valueEffecto[i] = -1;
            }
            else
            {
                valueEffecto[i] = to;
            }
        }
    }
}

classArco::~classArco()
{
}
