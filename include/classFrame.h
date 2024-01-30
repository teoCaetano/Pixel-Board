#ifndef CLASSFRAME_H
#define CLASSFRAME_H

#include <vector>
#include <algorithm>

class classFrame
{
private:
    int height_cl;
    int width_cl;
    int frameBuffer;
    std::vector<int> XCordenates;
    std::vector<int> YCordinates;
    //radio
    std::vector<int> radCordenates;
    //grados
    std::vector<int> gradCordenates;
    std::vector<int> gradMapCordinates;
    std::vector<int> pixelsPerRadio;
    /*
    @brief crea el mapa con los valores XY de los pixeles de la matriz, en matrices impares existe la posicion 0 en matrices pares no
    */
    void constructorXY();
    /*
    @brief convierte los valores de X e Y en cordenadas polares
    */
    void constructorPolar();
    /*
    @brief convierte los valores de grados a una sumatoria de naturales
    */
    void constructorMapDegre();
public:
    /*
    @brief es el constructor de la clase toma como parametros la altura y el ancho de la matrix en pixeles
    e inicializa los vectores para los distintos metodos de la clase
    @param {int} heigh altura de la matriz
    @param {int} width ancho matriz
    */
    classFrame(int heigh, int width);
    // devuelve el mayor radio dentro del mapa
    int getMaxRadio();
    // devuelve el mayor grado dentro de un anillo determinado del mapa
    // @param {int} ring radio del mapa
    int getMaxDegre(int ring);
    // devueve el menor grado dentro de un anillo determinado del mapa
    // @param {int} ring radio del mapa
    int getMinDegre(int ring);
    // devuelve la cantidad de pixeles en un radio determinado
    // @param {int} ring radio del mapa
    int getPixelsPerRadio(int ring);
    ~classFrame();
};

#endif  // CLASSFRAME_H
