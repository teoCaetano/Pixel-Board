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
    // @brief devuelve el mayor radio dentro del mapa
    int getMaxRadio();
    // @brief devuelve el mayor grado dentro de un anillo determinado del mapa
    // @param {int} ring radio del mapa
    int getMaxDegre(int ring);
    // @brief devueve el menor grado dentro de un anillo determinado del mapa
    // @param {int} ring radio del mapa
    int getMinDegre(int ring);
    // @brief devuelve la cantidad de pixeles en un radio determinado
    // @param {int} ring radio del mapa
    int getPixelsPerRadio(int ring);
    // @brief devuelve la posicio en el vector de determinado punto X Y
    // @param {int} X 
    // @param {int} Y
    int getAdressFromXY(int X, int Y);
    // @brief devuelve la posicion en el vector de determinado punto radio y grado
    // @param {int} rad - radio del punto
    // @param {int} grad - grado del punto
    int getAdressFromPolar(int rad, int grad);
    // @brief devuleve la posicion de el vector de deerminado punto radio y pixelNumRad
    // @param {int} rad - radio del punto
    // @param {int} mapGrad - numero del pixel de determinado radio
    int getAdressFromMapDegre(int rad, int mapGrad);
    // @brief devuelve el valor de X de determinada posicion de el vector
    // @param  {int} adr la posicion del vector
    int getXFromAdress(int adr);
    // @brief devuelve el valor de Y de determinada posicion de el vector
    // @param  {int} adr la posicion del vector
    int getYFromAdress(int adr);
    // @brief devuelve el valor de Radio de determinada posicion de el vector 
    // @param  {int} adr la posicion del vector  
    int getRadFromAdress(int adr);
    // @brief devuelve el valor de Angulo de determinada posicion de el vector
    // @param  {int} adr la posicion del vector
    int getGradFromAdress(int adr);
    // @brief devuelve el valor de el numero de pixel de radio de determinada posicion de el vector
    // @param  {int} adr la posicion del vector
    int getMapGradFromAdress(int adr);
    // @brief destructor classe
    ~classFrame();
};

#endif  // CLASSFRAME_H
