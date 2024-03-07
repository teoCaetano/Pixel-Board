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
    int bufferHue = 0;
    float bufferAmplitud = 0;
    int minAng = 0;
    int maxAng = 359;
    float valX = 0;
    float valY = 0;
    void uint8Rango(int &val);
    FastNoiseLite insideWarp;
    classFrame &algo;

public:
    std::vector<int> hueEffecto;
    std::vector<int> saturationEffecto;
    std::vector<int> valueEffecto;

    std::vector<int> hueNoise;
    std::vector<int> saturationNoise;
    std::vector<int> valueNoise;

    void setNoiseWarp(FastNoiseLite::DomainWarpType domainType, float amp, float frec);
    void setNoiseWarpSeed(int seed);
    void setAlmaNoiseTo(FastNoiseLite objetoNs, std::vector<int> &vec, int mapTo);

    void setAlmaFade(std::vector<int> &vec, int from, int to);
    void setAlmaTo(std::vector<int> &vec, int to);
    void setAlmaRingsFade(std::vector<int> &vec, int from, int to);
    // setea el anillo a to
    void setAlmaRingTo(std::vector<int> &vec, int ring, int to);

    void desplazoAngulo(int angulo);

    void setBufferHue(int hue);
    int getBufferHue();

    void setBufferAmplitud(float amplitud);
    float getBufferAmplitud();

    void writeToFrame();

    classAlma(classFrame &algo);
    ~classAlma();
};

classAlma::classAlma(classFrame &algooo) : algo(algooo)
{
    frameBufferSize_ef = algo.getFrameBufferSize();
    hueEffecto.resize(frameBufferSize_ef, 0);
    saturationEffecto.resize(frameBufferSize_ef, 0);
    valueEffecto.resize(frameBufferSize_ef, 0);
    hueNoise.resize(frameBufferSize_ef, 0);
    saturationNoise.resize(frameBufferSize_ef, 0);
    valueNoise.resize(frameBufferSize_ef, 0);
    insideWarp.SetSeed(random(0, 2000));
}

void classAlma::uint8Rango(int &val)
{
    if (val > 255)
    {
        val = 255;
    }
    if (val < 0)
    {
        val = 0;
    }
}

void classAlma::writeToFrame()
{
    int hue_CA_WTF = 0;
    int sat_CA_WTF = 0;
    int val_CA_WTF = 0;
    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        hue_CA_WTF = hueEffecto[i] + hueNoise[i];
        sat_CA_WTF = saturationEffecto[i] + saturationNoise[i];
        val_CA_WTF = valueEffecto[i] + valueNoise[i];

        uint8Rango(hue_CA_WTF);
        uint8Rango(sat_CA_WTF);
        uint8Rango(val_CA_WTF);

        algo.setHueFromAdress(i, hue_CA_WTF);
        algo.setSatFromAdress(i, sat_CA_WTF);
        algo.setValFromAdress(i, val_CA_WTF);
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

void classAlma::setAlmaRingTo(std::vector<int> &vec, int ring, int to)
{
    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        if (algo.getRadFromAdress(i) == ring)
        {
            vec[i] = to;
        }
    }
}

void classAlma::setAlmaRingsFade(std::vector<int> &vec, int from, int to)
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

void classAlma::setAlmaFade(std::vector<int> &vec, int from, int to)
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

void classAlma::setAlmaTo(std::vector<int> &vec, int to)
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

void classAlma::setNoiseWarpSeed(int seed)
{
    insideWarp.SetSeed(seed);
}

void classAlma::setNoiseWarp(FastNoiseLite::DomainWarpType domainType, float amp, float frec)
{
    insideWarp.SetFrequency(frec);
    insideWarp.SetDomainWarpType(domainType);
    insideWarp.SetDomainWarpAmp(amp);
}

void classAlma::setAlmaNoiseTo(FastNoiseLite objetoNs, std::vector<int> &vec, int mapTo)
{

    float val = 0;
    int val_int = 0;

    for (int i = 0; i < frameBufferSize_ef; i++)
    {
        valX = algo.getXFromAdress(i) / 10.0f;
        valY = algo.getYFromAdress(i) / 10.0f;
        insideWarp.DomainWarp(valX, valY);
        val = objetoNs.GetNoise(valX, valY);
        val = val * mapTo;
        val_int = val;
        uint8Rango(val_int);
        vec[i] = val;
    }
}

void classAlma::setBufferHue(int hue)
{
    if ((hue <= 255) && (hue >= 0))
    {
        bufferHue = hue;
    }
}

int classAlma::getBufferHue()
{
    return bufferHue;
}

void classAlma::setBufferAmplitud(float amplitud)
{
    if ((amplitud <= 2.55) && (amplitud >= 0))
    {
        bufferAmplitud = amplitud;
    }
}

float classAlma::getBufferAmplitud()
{
    return bufferAmplitud;
}

classAlma::~classAlma()
{
}
