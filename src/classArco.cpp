#include <Arduino.h>
#include <FastLED.h>
#include <vector>
#include <algorithm>
#include "classFrame.h"

class classArco
{
private:
    int frameBufferSize_ef;
    int minAng;
    int maxAng;

    classFrame &algo;

public:
    std::vector<int> hueEffecto;
    std::vector<int> saturationEffecto;
    std::vector<int> valueEffecto;
    std::vector<bool> ringEnable;

    classArco(classFrame &algooo);

    void setAngluoInValues(int minA, int maxA);

    void setArcoTo(std::vector<int> &vec, int to);
    void setArcoFade(std::vector<int> &vec, int from, int to);
    void setArcoRingsFade(std::vector<int> &vec, int from, int to);

    void writeToFrame();

    void desplazoAngulo(int angulo);
    void aumentoAngulo(int angulo);

    void allRings();
    void removeRing(int ring);
    void addRing(int ring);

    ~classArco();
};

classArco::classArco(classFrame &algooo) : algo(algooo)
{
    frameBufferSize_ef = algo.getFrameBufferSize();
    hueEffecto.resize(frameBufferSize_ef, -1);
    saturationEffecto.resize(frameBufferSize_ef, -1);
    valueEffecto.resize(frameBufferSize_ef, -1);
    ringEnable.resize(frameBufferSize_ef, true);
}

void classArco::writeToFrame()
{
    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        if (ringEnable[i] == true)
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
}

void classArco::aumentoAngulo(int angulo)
{
    maxAng += angulo;
    if (maxAng < 0)
    {
        maxAng += 360;
    }
    if (maxAng > 360)
    {
        maxAng -= 360;
    }
}

void classArco::desplazoAngulo(int angulo)
{
    minAng += angulo;
    maxAng += angulo;
    if (minAng < 0)
    {
        minAng += 360;
    }
    if (minAng > 360)
    {
        minAng -= 360;
    }
    if (maxAng < 0)
    {
        maxAng += 360;
    }
    if (maxAng > 360)
    {
        maxAng -= 360;
    }
}

void classArco::setAngluoInValues(int minA, int maxA)
{
    minAng = minA;
    maxAng = maxA;
    if (minAng < 0)
    {
        minAng = 0;
    }
    if (minAng > 360)
    {
        minAng = 360;
    }
    if (maxAng < 0)
    {
        maxAng = 0;
    }
    if (maxAng > 360)
    {
        maxAng = 360;
    }
}

void classArco::setArcoRingsFade(std::vector<int> &vec, int from, int to)
{
    int maxRad = algo.getMaxRadioValido();
    int minRad = algo.getMinRadio();
    int rad_i = 0;
    int angulo_i = 0;
    int angulo_im = 0;
    int maxAng_m = 0;
    int Local = 0;
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
        rad_i = algo.getRadFromAdress(i);
        if (modo_maxmax == true)
        {
            Local = map(rad_i, minRad, maxRad, from, to);
            if ((angulo_i <= maxAng) && (angulo_i >= minAng))
            {
                vec[i] = Local;
            }
            else
            {
                vec[i] = -1;
            }
        }
        if (modo_maxmin == true)
        {
            if (angulo_i <= maxAng)
            {
                angulo_im = angulo_i;
                angulo_im = angulo_im + 360;
            }
            else
            {
                angulo_im = angulo_i;
            }

            maxAng_m = maxAng + 360;

            Local = map(rad_i, minRad, maxRad, from, to);
            if ((angulo_im <= maxAng_m) && (angulo_im >= minAng))
            {
                vec[i] = Local;
            }
            else
            {
                vec[i] = -1;
            }
        }
    }
}

void classArco::setArcoFade(std::vector<int> &vec, int from, int to)
{
    int angulo_i = 0;
    int angulo_im = 0;
    int maxAng_m = 0;
    int Local = 0;
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
            Local = map(angulo_i, minAng, maxAng, from, to);
            if ((angulo_i < maxAng) && (angulo_i > minAng))
            {
                vec[i] = Local;
            }
            else
            {
                vec[i] = -1;
            }
        }
        if (modo_maxmin == true)
        {
            if (angulo_i <= maxAng)
            {
                angulo_im = angulo_i;
                angulo_im = angulo_im + 360;
            }
            else
            {
                angulo_im = angulo_i;
            }

            maxAng_m = maxAng + 360;

            Local = map(angulo_im, minAng, maxAng_m, from, to);
            if ((angulo_im <= maxAng_m) && (angulo_im >= minAng))
            {
                vec[i] = Local;
            }
            else
            {
                vec[i] = -1;
            }
        }
    }
}

void classArco::setArcoTo(std::vector<int> &vec, int to)
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
                vec[i] = to;
            }
            else
            {
                vec[i] = -1;
            }
        }
        if (modo_maxmin == true)
        {
            if ((angulo_i < minAng) && (angulo_i > maxAng))
            {
                vec[i] = -1;
            }
            else
            {
                vec[i] = to;
            }
        }
    }
}

void classArco::allRings()
{
    std::fill(ringEnable.begin(), ringEnable.end(), true);
}

void classArco::addRing(int ring)
{
    int valor = 0;
    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        valor = algo.getRadFromAdress(i);
        if (valor == ring)
        {
            ringEnable[i] = true;
        }
    }
}

void classArco::removeRing(int ring)
{
    int valor = 0;
    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        valor = algo.getRadFromAdress(i);
        if (valor == ring)
        {
            ringEnable[i] = false;
        }
    }
}

classArco::~classArco()
{
}
