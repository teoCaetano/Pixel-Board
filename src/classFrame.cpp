#include <Arduino.h>
#include <FastLED.h>
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
    void constructorXY();
    void constructorPolar();
    void constructorMapDegre();

public:
    classFrame(int heigh, int width);
    // devuelve el mayor radio dentro del mapa
    int getMaxRadio();
    // devuelve el mayor grado dentro de un anillo determinado del mapa
    int getMaxDegre(int ring);
    // devueve el menor grado dentro de un anillo determinado del mapa
    int getMinDegre(int ring);
    // devuelve la cantidad de pixeles en un radio determinado
    int getPixelsPerRadio(int ring);

    ~classFrame();
};

classFrame::classFrame(int heigh, int width)
{
    height_cl = heigh;
    width_cl = width;
    frameBuffer = width_cl * height_cl;
    XCordenates.resize(frameBuffer, 0);
    YCordinates.resize(frameBuffer, 0);
    radCordenates.resize(frameBuffer, 0);
    gradCordenates.resize(frameBuffer, 0);
    gradMapCordinates.resize(frameBuffer, 0);
    constructorXY();
    constructorPolar();
    constructorMapDegre();
}

void classFrame::constructorXY()
{
    bool restoHeight;
    bool restoWidth;
    int suma = 0;
    Serial.println("                                     ");
    if (height_cl % 2 == 1)
    {
        restoHeight = true;
    }
    else
    {
        restoHeight = false;
    }
    if (width_cl % 2 == 1)
    {
        restoWidth = true;
    }
    else
    {
        restoWidth = false;
    }
    if (restoWidth == true)
    {
        int index = 0;
        for (int Y = 0; Y < height_cl; Y++)
        {
            for (int X = -(width_cl / 2); X < (width_cl / 2) + 1; X++)
            {
                XCordenates[index] = X;
                index = index + 1;
            }
        }
    }
    if (restoHeight == true)
    {
        int index = 0;
        for (int Y = (height_cl / 2); Y >= -(height_cl / 2); Y--)
        {
            for (int X = 0; X < width_cl; X++)
            {
                YCordinates[index] = Y;
                index = index + 1;
            }
        }
    }
    if (restoWidth == false)
    {
        int index = 0;
        for (int Y = 0; Y < height_cl; Y++)
        {
            for (int X = -(width_cl / 2); X <= (width_cl / 2); X++)
            {
                if (X == 0)
                {
                    X = 1;
                }
                XCordenates[index] = X;
                index = index + 1;
            }
        }
    }
    if (restoHeight == false)
    {
        int index = 0;
        for (int Y = (height_cl / 2); Y >= -(height_cl / 2); Y--)
        {
            for (int X = 0; X < width_cl; X++)
            {
                int valueY = Y;
                if (valueY <= 0)
                {
                    valueY = valueY - 1;
                }
                YCordinates[index] = valueY;
                index = index + 1;
            }
        }
    }
    if (false)
    {
        for (int i = 0; i < height_cl; i++)
        {
            for (int w = 0; w < width_cl; w++)
            {
                if (XCordenates[suma]<0)
                {
                    Serial.print("  ");
                }
                else{
                    Serial.print("   ");
                }
                Serial.print(XCordenates[suma]);
                if (YCordinates[suma]<0)
                {
                    Serial.print("  ");
                }
                else{
                    Serial.print("   ");
                }
                Serial.print(YCordinates[suma]);
                delay(100);
                suma = suma + 1;
            }
            Serial.println(" ");
        }
        delay(500000);
    }
}

void classFrame::constructorPolar()
{
    double valor_X = 0;
    double valor_Y = 0;
    double radio = 0;
    double angulo = 0;
    int suma = 0;
    Serial.println("                                     ");
    for (int index = 0; index < frameBuffer; index++)
    {
        valor_X = XCordenates[index];
        valor_Y = YCordinates[index];

        // calculo la hipotenusa
        radio = (valor_X * valor_X) + (valor_Y * valor_Y);
        radio = sqrt(radio);

        radCordenates[index] = radio;

        angulo = atan2(valor_Y, valor_X);
        angulo = angulo * (180 / PI);

        if (angulo < 0)
        {
            angulo = 360 + angulo;
        }

        gradCordenates[index] = angulo;
    }
    if (false)
    {
        for (int i = 0; i < height_cl; i++)
        {
            for (int w = 0; w < width_cl; w++)
            {
                Serial.print("   ");
                Serial.print(radCordenates[suma]);
                Serial.print("   ");
                Serial.print(gradCordenates[suma]);
                delay(100);
                suma = suma + 1;
            }
            Serial.println(" ");
        }
        delay(500000);
    }
}

int classFrame::getMaxRadio()
{
    int max = radCordenates[0];
    for (int i = 0; i < frameBuffer; i++)
    {
        if (radCordenates[i] > max)
        {
            max = radCordenates[i];
        }
    }
    return max;
}

int classFrame::getMaxDegre(int ring)
{
    int max = 0;
    for (int i = 0; i < frameBuffer; i++)
    {
        if (radCordenates[i] == ring)
        {
            if (gradCordenates[i] > max)
            {
                max = gradCordenates[i];
            }
        }
    }
    return max;
}

int classFrame::getMinDegre(int ring)
{
    int min = 360;
    for (int i = 0; i < frameBuffer; i++)
    {
        if (radCordenates[i] == ring)
        {
            if (gradCordenates[i] < min)
            {
                min = gradCordenates[i];
            }
        }
    }
    return min;
}

int classFrame::getPixelsPerRadio(int ring)
{
    int suma = 0;

    for (int X = 0; X < frameBuffer; X++)
    {
        if (radCordenates[X] == ring)
        {
            suma = suma + 1;
        }
    }
    return suma;
}


void classFrame::constructorMapDegre(){
    int maxRings = getMaxRadio();
    int pixels = 0;
    int index = 0;
    std::vector<int> gradosRadio;
    for (int R = 0; R <= maxRings; R++)
    {
        index = 0 ;
        pixels = getPixelsPerRadio(R);
        
        gradosRadio.clear();

        for (int i = 0; i < frameBuffer; i++)
        {
            if (radCordenates[i]==R)
            {
                gradosRadio.push_back(gradCordenates[i]);
            }
            
        }
        std::sort(gradosRadio.begin(), gradosRadio.end());
        for (int P = 0; P < pixels; P++)
        {
            for (int i = 0; i < frameBuffer; i++)
            {
                if (radCordenates[i]==R)
                {
                    if (gradCordenates[i]==gradosRadio[index])
                    {
                        gradMapCordinates[i]=index;
                        index++;
                    }
                }
            }
        }
    }
    if (false)
    {
        int suma = 0;
        for (int i = 0; i < height_cl; i++)
        {
            for (int w = 0; w < width_cl; w++)
            {
                if ((gradMapCordinates[suma]/10)<1)
                {
                    Serial.print("   ");
                }
                else{
                    Serial.print("  ");
                }
                Serial.print(gradMapCordinates[suma]);
                delay(100);
                suma = suma + 1;
            }
            Serial.println(" ");
        }
        delay(500000);
    }
}

classFrame::~classFrame()
{
}
