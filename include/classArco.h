#ifndef CLASSARCO_H
#define CLASSARCO_H

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

#endif