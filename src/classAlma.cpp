#include <Arduino.h>
#include <FastLED.h>
#include <vector>
#include <algorithm>
#include "classFrame.h"
#include "FastNoiseLite.h"

class classAlma
{
private:
    int frameBufferSize_ef;
    int minAng = 0;
    int maxAng = 359;

public:
    std::vector<int> hueEffecto;
    std::vector<int> saturationEffecto;
    std::vector<int> valueEffecto;

    void setAlmaNoiseTo(classFrame algo, FastNoiseLite objetoNs, std::vector<int> &vec, int mapTo);

    void setAlmaFade(classFrame algo, std::vector<int> &vec, int from, int to);
    void setAlmaTo(classFrame algo, std::vector<int> &vec, int to);
    void setAlmaRingsFade(classFrame algo, std::vector<int> &vec, int from, int to);
    void setAlmaRingTo(classFrame algo, std::vector<int> &vec, int ring, int to);

    void desplazoAngulo(int angulo);

    void writeToFrame(classFrame &algo);

    classAlma(classFrame algo);
    ~classAlma();
};

classAlma::classAlma(classFrame algo)
{
    frameBufferSize_ef = algo.getFrameBufferSize();
    hueEffecto.resize(frameBufferSize_ef, -1);
    saturationEffecto.resize(frameBufferSize_ef, -1);
    valueEffecto.resize(frameBufferSize_ef, -1);
}

void classAlma::writeToFrame(classFrame &algo)
{
    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        algo.setHueFromAdress(i, hueEffecto[i]);
        algo.setSatFromAdress(i, saturationEffecto[i]);
        algo.setValFromAdress(i, valueEffecto[i]);
    }
}

void classAlma::desplazoAngulo(int angulo)
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

void classAlma::setAlmaRingTo(classFrame algo, std::vector<int> &vec, int ring, int to)
{
    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        if (algo.getRadFromAdress(i) == ring)
        {
            vec[i] = to;
        }
    }
}

void classAlma::setAlmaRingsFade(classFrame algo, std::vector<int> &vec, int from, int to)
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
        }
    }
}

void classAlma::setAlmaFade(classFrame algo, std::vector<int> &vec, int from, int to)
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
        }
    }
}

void classAlma::setAlmaTo(classFrame algo, std::vector<int> &vec, int to)
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
            if ((angulo_i < maxAng) && (angulo_i > minAng))
            {
                vec[i] = to;
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

            if ((angulo_im <= maxAng_m) && (angulo_im >= minAng))
            {
                vec[i] = to;
            }
        }
    }
}

void classAlma::setAlmaNoiseTo(classFrame algo, FastNoiseLite objetoNs, std::vector<int> &vec, int mapTo)
{
    float valX = 0;
    float valY = 0;
    float val = 0;
    int valToWirite = 0;
    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        valX = algo.getXFromAdress(i) / 10.0f;
        valY = algo.getYFromAdress(i) / 10.0f;
        objetoNs.DomainWarp(valX, valY);
        val = objetoNs.GetNoise(valX, valY);
        val = val * mapTo;
        valToWirite = val + vec[i];
        if (valToWirite > 255)
        {
            vec[i] = 255;
        }
        else if (valToWirite < 0)
        {
            vec[i] = 0;
        }
        else
        {
            vec[i] = valToWirite;
        }
    }
}

classAlma::~classAlma()
{
}
