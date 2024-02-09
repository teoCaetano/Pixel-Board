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
    int maxAng = 360;

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

#endif