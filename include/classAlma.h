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
    // @brief recive un valor y lo mantiene el el rango 0 a 255
    // @param{int} val valor a restringir
    void uint8Rango(int &val);
    // @brief objeto para generar el Warp o desplazamiento del ruido
    FastNoiseLite insideWarp;
    // @brief variable que almacena la referencia a el objeto de la clase clasFrame
    classFrame &algo;

public:
    //---------------------------------------------------------------------------------
    // Vectores
    //---------------------------------------------------------------------------------
    std::vector<int> hueEffecto;
    std::vector<int> saturationEffecto;
    std::vector<int> valueEffecto;

    std::vector<int> hueNoise;
    std::vector<int> saturationNoise;
    std::vector<int> valueNoise;

    //---------------------------------------------------------------------------------
    // Funciones Noise
    //---------------------------------------------------------------------------------

    /*
     @brief toma como parametro los valores para configurar insideWarp
     @param{FastNoiseLite::DomainWarpType} domainType define el tipo del warp
     @param{float} amp - es el valor de la amplitud, es el valor que se cambia para generar movimiento
     @param{float} frec - es el valor de la frecuencia del warp, para generar un movimiento "agradable" dejar en 0
    */
    void setNoiseWarp(FastNoiseLite::DomainWarpType domainType, float amp, float frec);
    /*

    */
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