#ifndef CLASSALMA_H
#define CLASSALMA_H

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
    void setAlmaNoiseTo(FastNoiseLite objetoNs, std::vector<int> &vec, int mapTo);

    void setAlmaFade(std::vector<int> &vec, int from, int to);
    void setAlmaTo(std::vector<int> &vec, int to);
    void setAlmaRingsFade(std::vector<int> &vec, int from, int to);
    void setAlmaRingTo(std::vector<int> &vec, int ring, int to);

    void desplazoAngulo(int angulo);

    void writeToFrame();

    classAlma(classFrame &algo);
    ~classAlma();
};

#endif