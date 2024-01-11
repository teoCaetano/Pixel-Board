#ifndef CLASSFRAME_H
#define CLASSFRAME_H

#include <vector>

class classFrame
{
private:
    int height_cl;
    int width_cl;
    int frameBuffer;
    std::vector<int> XCordenates;
    std::vector<int> YCordinates;
    std::vector<int> radCordenates;
    std::vector<int> gradCordenates;
    std::vector<int> gradMapCordinates;
    std::vector<int> clLienzoHue;
    std::vector<int> clLienzoSaturacion;
    std::vector<int> clLienzoValue;
    std::vector<int> pixelsPerRadio;
    void constructorXY();

public:
    classFrame(int heigh, int width);
    void constructorPolar(int x, int Y);
    // devuelve el mayor radio dentro del mapa
    int getMaxRadio();
    // devuelve el mayor grado dentro de un anillo determinado del mapa
    int getMaxDegre(int ring);
    // devueve el menor grado dentro de un anillo determinado del mapa
    int getMinDegre(int ring);
    // devuelve la cantidad de pixeles en un radio determinado
    int getPixelsPerRadio(int ring);
    //guarda los valores de pixel por radio en un array
    void fill_pixelsPerRadio();
    ~classFrame();
};

#endif  // CLASSFRAME_H
