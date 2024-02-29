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
    //---------------------------------------------------------------------------------
    // Vectores
    //---------------------------------------------------------------------------------
    std::vector<int> hueEffecto;
    std::vector<int> saturationEffecto;
    std::vector<int> valueEffecto;
    std::vector<bool> ringEnable;

    classArco(classFrame algooo);

    void setAngluoInValues(int minA, int maxA);
    //---------------------------------------------------------------------------------
    // Funciones efecto
    //---------------------------------------------------------------------------------
    /*
     @brief  establece los valores del vector que recive como parametro al valor TO
     @param {std::vector<int>}  vector el cual se escribe 
     @param {int}  valor que se escribe en el vector  
    */
    void setArcoTo(std::vector<int> &vec, int to);
    /*
     @brief  establece un fade en el angulo del objeto entre 2 parametros y lo escribe al vector
     @param {std::vector<int>}  vector el cual se escribe 
     @param {int} from valor inicial del fade
     @param {int} to valor final del fade
    */
    void setArcoFade(std::vector<int> &vec, int from, int to);
    /*
     @brief  establece un fade con respecto a los anillos 
     @param {std::vector<int>}  vector el cual se escribe 
     @param {int} from valor inicial del fade
     @param {int} to valor final del fade
    */
    void setArcoRingsFade(std::vector<int> &vec, int from, int to);
    /*
     @brief escribe los valores de los buffers del efecto a los buffers del frame ademas le suma los buffers con ruido
    */
    void writeToFrame();
    /*
     @brief desplaza el angulo tantos grados
     @param {int} angulo a desplazar
    */
    void desplazoAngulo(int angulo);
    /*
     @brief aumenta el angulo tantos grados
     @param {int} angulo a aumentar
    */
    void aumentoAngulo(int angulo);
    //@brief llena el vector enableRing con true
    void allRings();
    /*
     @brief llena el vector enableRing con false en el anillo
     @param {int} anillo 
    */
    void removeRing(int ring);
    /*
     @brief llena el vector enableRing con true en el anillo
     @param {int} anillo
    */
    void addRing(int ring);

    ~classArco();
};
#endif