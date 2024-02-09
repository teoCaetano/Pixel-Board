#ifndef CLASSARCO_H
#define CLASSARCO_H

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

    classArco(classFrame algooo);

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
#endif