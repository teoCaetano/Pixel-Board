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

public:
    std::vector<int> hueEffecto;
    std::vector<int> saturationEffecto;
    std::vector<int> valueEffecto;
    std::vector<bool> ringEnable;

    classArco(classFrame algo);

    void setAngluoInValues(int minA, int maxA);

    void setArcoTo(classFrame algo, std::vector<int> &vec, int to);
    void setArcoFade(classFrame algo, std::vector<int> &vec, int from, int to);
    void setArcoRingsFade(classFrame algo, std::vector<int> &vec, int from, int to);

    void writeToFrame(classFrame &algo);

    void desplazoAngulo(int angulo);
    void aumentoAngulo(int angulo);

    void allRings();
    void removeRing(classFrame algo, int ring);
    void addRing(classFrame algo, int ring);

    ~classArco();
};
#endif