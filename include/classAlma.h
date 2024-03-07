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
    int bufferHue = 0;
    float bufferAmplitud = 0;
    float valX = 0;
    float valY = 0;
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
    void setNoiseWarpSeed(int seed);
    /*
     @brief toma como parametro los valores para configurar insideWarp
     @param{FastNoiseLite::DomainWarpType} domainType define el tipo del warp
     @param{float} amp - es el valor de la amplitud, es el valor que se cambia para generar movimiento
     @param{float} frec - es el valor de la frecuencia del warp, para generar un movimiento "agradable" dejar en 0
    */
    void setNoiseWarp(FastNoiseLite::DomainWarpType domainType, float amp, float frec);
    /*
     @brief toma el ruido de el objetoNs lo pasa por el DomainWarp lo multiplica por mapTo y lo escrive al vector vec
     @param{FastNoiseLite} objetoNs - es el objeto con el ruido
     @param{std::vector<int>} vec - es el vector al cual escribo el ruido
     @param{int} mapTo - el valor por el cual multiplico el ruido(el ruido es un valor de -1 a +1)
    */
    void setAlmaNoiseTo(FastNoiseLite objetoNs, std::vector<int> &vec, int mapTo);
    /*
     @brief genera un fade entre los angulos
     @param{std::vector<int>} vec - el vector al cual almaceno los valores del fade
     @param{int} from - el valor inicial del fade
     @param{int} to - el valor final del fade
    */
    //---------------------------------------------------------------------------------
    // Funciones Alma
    //---------------------------------------------------------------------------------
    void setAlmaFade(std::vector<int> &vec, int from, int to);
    /*
     @brief setea un array a un valor especifico
     @param{std::vector<int>} vec - vector en el cual escribo to
     @param{int}to - valor a escribir
    */
    void setAlmaTo(std::vector<int> &vec, int to);
    /*
     @brief genera un fade con respecto a los anillos
     @param{std::vector<int>} vec - el vector al cual almaceno los valores del fade
     @param{int} from - el valor inicial del fade
     @param{int} to - el valor final del fade
    */
    void setAlmaRingsFade(std::vector<int> &vec, int from, int to);
    /*
     @brief setea un anillo a un valor especifico
     @param{std::vector<int>} vec - vector en el cual escribo to
     @param{int}to - valor a escribir
    */
    void setAlmaRingTo(std::vector<int> &vec, int ring, int to);
    /*
     @brief gira el efecto una cierta cantida de angulos
     @param{int}angulo
    */
    void desplazoAngulo(int angulo);
    /*
     @brief escribe los valores de los buffers del efecto a los buffers del frame ademas le suma los buffers con ruido
    */
    void setBufferHue(int hue);
    int getBufferHue();

    void setBufferAmplitud(float amplitud);
    float getBufferAmplitud();

    void writeToFrame();

    classAlma(classFrame &algo);
    ~classAlma();
};

#endif