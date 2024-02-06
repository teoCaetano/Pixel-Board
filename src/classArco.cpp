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

public:
    std::vector<int> hueEffecto;
    std::vector<int> saturationEffecto;
    std::vector<int> valueEffecto;

    classArco(classFrame algo);

    void setAngluoInValues(int minA, int maxA);

    void setArcoTo(classFrame algo, std::vector<int> &vec, int to);
    void setArcoFade(classFrame algo, std::vector<int> &vec, int from, int to);
    void setArcoRingsFade(classFrame algo, std::vector<int> &vec, int from, int to);

    void writeToFrame(classFrame &algo);

    void desplazoAngulo(int angulo);
    void aumentoAngulo(int angulo);
    ~classArco();
};

classArco::classArco(classFrame algo)
{
    frameBufferSize_ef = algo.getFrameBufferSize();
    hueEffecto.resize(frameBufferSize_ef, -1);
    saturationEffecto.resize(frameBufferSize_ef, -1);
    valueEffecto.resize(frameBufferSize_ef, -1);
}

void classArco::writeToFrame(classFrame &algo)
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

void classArco::setArcoRingsFade(classFrame algo, std::vector<int> &vec, int from, int to)
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

void classArco::setArcoFade(classFrame algo, std::vector<int> &vec, int from, int to)
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

void classArco::setArcoTo(classFrame algo, std::vector<int> &vec, int to)
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

classArco::~classArco()
{
}
