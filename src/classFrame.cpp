#include <Arduino.h>
#include <FastLED.h>
#include <vector>
#include <algorithm>

//-----------------------------------------------------------------------------------------------------------------------------------------
// define the test as true to get the values in the serial monitor
//-----------------------------------------------------------------------------------------------------------------------------------------

#define TEST_CARTESIANO false
#define TEST_POOLARES false
#define TEST_HUE false
#define TEST_SATURATION false
#define TEST_VALUE false
#define TEST_MATRIX false
#define TEST_PIXELS_PER_ROW false
#define TEST_MAX_LEDS_PER_ROW false
#define TEST_LEDS_PER_PIXEL false

class classFrame
{
private:
    int height_cl;
    int width_cl;
    int frameBufferSize;
    bool serpenty_cl;
    bool start_cl;
    bool simetria_cl;
    bool round_cl;
    // cartesiano
    std::vector<int> XCordenates;
    std::vector<int> YCordinates;
    // radio
    std::vector<int> radCordenates;
    // grados
    std::vector<int> gradCordenates;
    std::vector<int> gradMapCordinates;
    std::vector<int> pixelsPerRadio;
    // matrix
    std::vector<int> ledsPerPixel;
    std::vector<int> pixelLedMap;
    // HSV
    std::vector<uint8_t> hueBuffer;
    std::vector<uint8_t> valueBuffer;
    std::vector<uint8_t> saturationBuffer;

public:
    classFrame(int heigh, int width);
    //-------------------------------------------------------------------------------------------
    // buffer methods
    //-------------------------------------------------------------------------------------------
    void updateFrameBuffer(uint8_t buffer[][3]);
    void clearBuffer();
    //-------------------------------------------------------------------------------------------
    // constructors
    //-------------------------------------------------------------------------------------------
    void constructorXY();
    void constructorPolar();
    void constructorMapDegre();
    // construye el array de valores para poder mostrar la imagen en la matriz
    void matrixConstructor(bool serpenty, bool start, bool simetria, int lesdPPixel, bool round);
    //-------------------------------------------------------------------------------------------
    // write
    //-------------------------------------------------------------------------------------------
    void writeLedsPerPixelsTo(int lesdspixels[]);
    void writepixelLedMapTo(int ledsMap[]);
    //-------------------------------------------------------------------------------------------
    // geter
    //-------------------------------------------------------------------------------------------
    // devuelve el tamaño del frame buffer size
    int getFrameBufferSize();
    // devuelve el menor radio dentro del mapa
    int getMinRadio();
    // devuelve el mayor radio dentro del mapa
    int getMaxRadio();
    // devuelve el mayor radio dentro del mapa, pero discrimina si round == true(pantalla redonda)
    int getMaxRadioValido();
    // devuelve el mayor grado dentro de un anillo determinado del mapa
    int getMaxDegre(int ring);
    // devueve el menor grado dentro de un anillo determinado del mapa
    int getMinDegre(int ring);
    // devuelve la cantidad de pixeles en un radio determinado
    int getPixelsPerRadio(int ring);
    // devuelve la posicion en el vector de determinado punto X Y
    int getAdressFromXY(int X, int Y);
    // devuelve la posicion en el vector de determinado punto radio y grado
    int getAdressFromPolar(int rad, int grad);
    // devuleve la posicion de el vector de deerminado punto radio y pixelNumRad
    int getAdressFromMapDegre(int rad, int mapGrad);
    // devuelve el valor de x de determinada posicion de el vector
    int getXFromAdress(int adr);
    // devuelve el valor de y de determinada posicion de el vector
    int getYFromAdress(int adr);
    // devuelve el valor de Radio de determinada posicion de el vector
    int getRadFromAdress(int adr);
    // devuelve el valor de Angulo de determinada posicion de el vector
    int getGradFromAdress(int adr);
    // devuelve el valor de el numero de pixel de radio de determinada posicion de el vector
    int getMapGradFromAdress(int adr);

    int getHueFromAdress(int adr);
    int getSatFromAdress(int adr);
    int getValFromAdress(int adr);

    void setHueFromAdress(int adr, int value);
    void setSatFromAdress(int adr, int value);
    void setValFromAdress(int adr, int value);
    // destructor classe
    ~classFrame();
};

classFrame::classFrame(int heigh, int width)
{
    height_cl = heigh;
    width_cl = width;
    frameBufferSize = width_cl * height_cl;

    XCordenates.resize(frameBufferSize, 0);
    YCordinates.resize(frameBufferSize, 0);

    radCordenates.resize(frameBufferSize, 0);
    gradCordenates.resize(frameBufferSize, 0);
    gradMapCordinates.resize(frameBufferSize, 0);

    ledsPerPixel.resize(frameBufferSize, 0);
    pixelLedMap.resize(frameBufferSize, 0);

    hueBuffer.resize(frameBufferSize, 0);
    valueBuffer.resize(frameBufferSize, 0);
    saturationBuffer.resize(frameBufferSize, 0);
}

void classFrame::updateFrameBuffer(uint8_t buffer[][3])
{
    for (int i = 0; i < frameBufferSize; i++)
    {

        if (buffer[i][0] != hueBuffer[i])
        {
            buffer[i][0] = hueBuffer[i];
        }
        if (buffer[i][1] != saturationBuffer[i])
        {
            buffer[i][1] = saturationBuffer[i];
        }
        if (buffer[i][2] = valueBuffer[i])
        {
            buffer[i][2] = valueBuffer[i];
        }
    }
}
void classFrame::clearBuffer()
{
    std::fill(hueBuffer.begin(), hueBuffer.end(), 0);
    std::fill(saturationBuffer.begin(), saturationBuffer.end(), 0);
    std::fill(valueBuffer.begin(), valueBuffer.end(), 0);
}

void classFrame::matrixConstructor(bool serpenty, bool start, bool simetria, int lesdPPixel, bool round)
{
    int radioMaximo = 0;
    int suma = 0;

    serpenty_cl = serpenty;
    start_cl = start;
    simetria_cl = simetria;
    round_cl = round;

    // es un contador que sirve para desplazarce por el array
    int pixelsPerRow_suma = 0;
    // almacena el valor de pixeles por fila para guardarlo se resetea a 0 por cada fila
    int pixelsPerRow_value = 0;
    std::vector<int> pixelsPerRow;
    pixelsPerRow.resize(height_cl, 0);

    int maxLedsPerRow_resultado = 0;
    // va guardando el pixel con maxima denominacion de cada fila
    int maxLedsPerRow_suma = 0;
    std::vector<int> maxLedsPerRow;
    maxLedsPerRow.resize(height_cl, 0);

    /*
      sirve para calcular el radio maximo para el cual quiero calcular los leds
      en caso de round=true utilizo el ancho(WIDHT) para sacar el radio de la circunferencia
      en caso de round=false utilizao el valor del radio poolar del primer pixel del array
    */

    if (round == true)
    {
        radioMaximo = (width_cl / 2);
    }
    else
    {
        radioMaximo = getMaxRadio();
    }

    /*
      utilizo este for para almacenar los valores de la cantidad de pixeles por fila
    */
    // me desplazo por las filas
    for (int Y = 0; Y < height_cl; Y++)
    {
        pixelsPerRow_value = 0;
        for (int X = 0; X < width_cl; X++)
        {
            if (radCordenates[pixelsPerRow_suma] <= radioMaximo)
            {
                pixelsPerRow_value = pixelsPerRow_value + 1;
            }
            pixelsPerRow_suma = pixelsPerRow_suma + 1;
        }
        pixelsPerRow[Y] = pixelsPerRow_value;
        if (false)
        {
            Serial.println("test pixels per row");
            Serial.println(pixelsPerRow[Y]);
            delay(1000);
        }
    }
    /*
      utilizo este for para sacar el led con mayor denominacio de cada fila
    */

    for (int i = 0; i < height_cl; i++)
    {
        // aumento maxledsperrow la cantida de pixeles en la fila i
        maxLedsPerRow_suma += pixelsPerRow[i];
        // para sacar el led cuya posicion es el valor de maximo en esa fila
        // corrijo por -1 porque el array de leds comienza en 0, y multiplico por la cantidad de leds
        maxLedsPerRow_resultado = (maxLedsPerRow_suma - 1) * lesdPPixel;
        // almaceno
        maxLedsPerRow[i] = maxLedsPerRow_resultado;

        if (false)
        {
            Serial.println("test max leds per row");
            Serial.println(maxLedsPerRow_resultado);
            delay(1000);
        }
    }

    for (int i = 0; i < frameBufferSize; i++)
    {
        if (radCordenates[i] <= radioMaximo)
        {
            ledsPerPixel[i] = lesdPPixel;
        }
        else
        {
            ledsPerPixel[i] = 0;
        }
    }

    if (false)
    {
        int suma = 0;
        for (int i = 0; i < height_cl; i++)
        {
            for (int w = 0; w < width_cl; w++)
            {
                Serial.print("   ");
                Serial.print(ledsPerPixel[suma]);
                delay(100);
                suma = suma + 1;
            }
            Serial.println(" ");
        }
        delay(500000);
    }

    if ((serpenty == false) && (start == false)) // no serpenty empieza por la izquierda
    {
        int suma = 0;
        int valorLed = 0;
        for (int Y = 0; Y < height_cl; Y++)
        {
            valorLed = maxLedsPerRow[Y];
            for (int X = 0; X < width_cl; X++)
            {
                if (radCordenates[suma] <= radioMaximo)
                {
                    pixelLedMap[suma] = valorLed;
                    valorLed -= lesdPPixel;
                }
                suma += 1;
            }
        }
    }

    if ((serpenty == false) && (start == true)) // no serpenty empieza por la derecha
    {
        int suma = 0;
        int valorLed = 0;
        for (int Y = 0; Y < height_cl; Y++)
        {
            for (int X = 0; X < width_cl; X++)
            {
                if (radCordenates[suma] <= radioMaximo)
                {
                    pixelLedMap[suma] = valorLed;
                    valorLed += lesdPPixel;
                }
                suma += 1;
            }
        }
    }

    if ((serpenty == true) && (start == false)) // serpenty empieza por la izquierda
    {
        int suma = 0;
        int valorLed = 0;
        int par_impar = 0;
        for (int Y = 0; Y < height_cl; Y++)
        {
            par_impar++;
            if (par_impar % 2 == 1)
            {
                valorLed = maxLedsPerRow[Y];
                for (int X = 0; X < width_cl; X++)
                {
                    if (radCordenates[suma] <= radioMaximo)
                    {
                        pixelLedMap[suma] = valorLed;
                        valorLed -= lesdPPixel;
                    }
                    suma += 1;
                }
            }
            if (par_impar % 2 == 0)
            {
                valorLed = maxLedsPerRow[Y];
                valorLed = valorLed - (pixelsPerRow[Y] * lesdPPixel) + lesdPPixel;
                for (int X = 0; X < width_cl; X++)
                {
                    if (radCordenates[suma] <= radioMaximo)
                    {
                        pixelLedMap[suma] = valorLed;
                        valorLed += lesdPPixel;
                    }
                    suma += 1;
                }
            }
        }
    }
    if ((serpenty == true) && (start == true)) // serpenty empieza por la derecha
    {
        int suma = 0;
        int valorLed = 0;
        int par_impar = 0;
        for (int Y = 0; Y < height_cl; Y++)
        {
            // contador
            par_impar++;
            if (par_impar % 2 == 0)
            {
                valorLed = maxLedsPerRow[Y];
                for (int X = 0; X < width_cl; X++)
                {
                    if (radCordenates[suma] <= radioMaximo)
                    {
                        pixelLedMap[suma] = valorLed;
                        valorLed -= lesdPPixel;
                    }
                    suma += 1;
                }
            }
            if (par_impar % 2 == 1)
            {
                valorLed = maxLedsPerRow[Y];
                valorLed = valorLed - (pixelsPerRow[Y] * lesdPPixel) + lesdPPixel;
                for (int X = 0; X < width_cl; X++)
                {
                    if (radCordenates[suma] <= radioMaximo)
                    {
                        pixelLedMap[suma] = valorLed;
                        valorLed += lesdPPixel;
                    }
                    suma += 1;
                }
            }
        }
    }
    if (false)
    {
        suma = 0;
        for (int i = 0; i < height_cl; i++)
        {
            for (int w = 0; w < width_cl; w++)
            {
                Serial.print("   ");
                Serial.print(pixelLedMap[suma]);
                delay(100);
                suma = suma + 1;
            }
            Serial.println(" ");
        }
        delay(500000);
    }
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
        int valueX = -(width_cl / 2);
        for (int Y = 0; Y < height_cl; Y++)
        {
            for (int X = 0; X < width_cl; X++)
            {
                if (valueX == 0)
                {
                    valueX++;
                }
                if (index < frameBufferSize)
                {
                    XCordenates[index] = valueX;
                }
                valueX++;
                index = index + 1;
            }
            valueX = -(width_cl / 2);
        }
    }
    if (restoHeight == false)
    {
        int index = 0;
        int valueY = (height_cl / 2);
        for (int Y = 0; Y < height_cl; Y++)
        {
            for (int X = 0; X < width_cl; X++)
            {
                if (valueY == 0)
                {
                    valueY--;
                }
                if (index < frameBufferSize)
                {
                    YCordinates[index] = valueY;
                }
                index = index + 1;
            }
            valueY--;
        }
    }
    if (false)
    {
        for (int i = 0; i < height_cl; i++)
        {
            for (int w = 0; w < width_cl; w++)
            {
                if (XCordenates[suma] < 0)
                {
                    Serial.print("  ");
                }
                else
                {
                    Serial.print("   ");
                }
                Serial.print(XCordenates[suma]);
                if (YCordinates[suma] < 0)
                {
                    Serial.print("  ");
                }
                else
                {
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
// como esta este metodo solo maneja ambos lados pares o ambos lados impares
void classFrame::constructorPolar()
{
    double valor_X = 0;
    double valor_Y = 0;
    double radio = 0;
    double angulo = 0;
    int suma = 0;
    Serial.println("                                     ");
    for (int index = 0; index < frameBufferSize; index++)
    {
        valor_X = XCordenates[index];
        valor_Y = YCordinates[index];

        if (valor_X < 0)
        {
            valor_X = valor_X + 0.5f;
        }
        if (valor_X > 0)
        {
            valor_X = valor_X - 0.5f;
        }
        if (valor_Y < 0)
        {
            valor_Y = valor_Y + 0.5f;
        }
        if (valor_Y > 0)
        {
            valor_Y = valor_Y - 0.5f;
        }
        // calculo la hipotenusa
        radio = (valor_X * valor_X) + (valor_Y * valor_Y);
        // falta exepcion para un lado par y un lado impar o viceversa
        if (XCordenates[index] == 0 && YCordinates[index] == 0)
        {
            radio = sqrt(radio);
        }
        else
        {
            radio = sqrt(radio) + 1;
        }

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
    for (int i = 0; i < frameBufferSize; i++)
    {
        if (radCordenates[i] > max)
        {
            max = radCordenates[i];
        }
    }
    return max;
}

int classFrame::getMaxRadioValido()
{
    int valor = 0;
    if (round_cl == true)
    {
        if (0 == getMinRadio())
        {
            valor = width_cl / 2 - 1;
        }
        else
        {
            valor = width_cl / 2 ;
        }
    }
    else
    {
        int valor = radCordenates[0];
        for (int i = 0; i < frameBufferSize; i++)
        {
            if (radCordenates[i] > valor)
            {
                valor = radCordenates[i];
            }
        }
    }
    return valor;
}

int classFrame::getMinRadio()
{
    int min = radCordenates[0];
    for (int i = 0; i < frameBufferSize; i++)
    {
        if (radCordenates[i] < min)
        {
            min = radCordenates[i];
        }
    }
    return min;
}

int classFrame::getMaxDegre(int ring)
{
    int max = 0;
    for (int i = 0; i < frameBufferSize; i++)
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
    for (int i = 0; i < frameBufferSize; i++)
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

    for (int X = 0; X < frameBufferSize; X++)
    {
        if (radCordenates[X] == ring)
        {
            suma = suma + 1;
        }
    }
    return suma;
}

void classFrame::constructorMapDegre()
{
    int maxRings = getMaxRadio();
    int pixels = 0;
    int index = 0;
    std::vector<int> gradosRadio;

    for (int R = 0; R <= maxRings; R++)
    {
        index = 0;
        pixels = getPixelsPerRadio(R);

        gradosRadio.clear();

        for (int i = 0; i < frameBufferSize; i++)
        {
            if (radCordenates[i] == R)
            {
                gradosRadio.push_back(gradCordenates[i]);
            }
        }
        std::sort(gradosRadio.begin(), gradosRadio.end());
        for (int P = 0; P < pixels; P++)
        {
            for (int i = 0; i < frameBufferSize; i++)
            {
                if (radCordenates[i] == R)
                {
                    if (gradCordenates[i] == gradosRadio[index])
                    {
                        gradMapCordinates[i] = index;
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
                if ((gradMapCordinates[suma] / 10) < 1)
                {
                    Serial.print("   ");
                }
                else
                {
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

//---------------------------------------------------------------------------------------
// Geters methods
//---------------------------------------------------------------------------------------
int classFrame::getAdressFromXY(int X, int Y)
{
    int valor = 0;
    for (int i = 0; i < frameBufferSize; i++)
    {
        if (XCordenates[i] == X)
        {
            if (YCordinates[i] == Y)
            {
                valor = i;
            }
        }
    }
    Serial.println(valor);
    return valor;
}

int classFrame::getAdressFromPolar(int rad, int grad)
{
    int save = 0;
    int valor_min = 10000000;
    for (int i = 0; i < frameBufferSize; i++)
    {
        if (radCordenates[i] == rad)
        {
            if (abs(gradCordenates[i] - grad) < valor_min)
            {
                valor_min = gradCordenates[i] - grad;
                valor_min = abs(valor_min);
            }
        }
    }
    for (int i = 0; i < frameBufferSize; i++)
    {
        if (radCordenates[i] == rad)
        {
            if (abs(gradCordenates[i] - grad) == valor_min)
            {
                save = i;
            }
        }
    }
    return save;
}

int classFrame::getAdressFromMapDegre(int rad, int mapGrad)
{
    int save;
    for (int i = 0; i < frameBufferSize; i++)
    {
        if (radCordenates[i] == rad)
        {
            if (gradMapCordinates[i] == mapGrad)
            {
                save = i;
            }
        }
    }
    return save;
}

int classFrame::getXFromAdress(int adr)
{
    return XCordenates[adr];
}

int classFrame::getYFromAdress(int adr)
{
    return YCordinates[adr];
}

int classFrame::getRadFromAdress(int adr)
{
    return radCordenates[adr];
}

int classFrame::getGradFromAdress(int adr)
{
    return gradCordenates[adr];
}
int classFrame::getMapGradFromAdress(int adr)
{
    return gradMapCordinates[adr];
}

int classFrame::getFrameBufferSize()
{
    return frameBufferSize;
}

int classFrame::getHueFromAdress(int adr)
{
    return hueBuffer[adr];
}

int classFrame::getSatFromAdress(int adr)
{
    return saturationBuffer[adr];
}

int classFrame::getValFromAdress(int adr)
{
    return valueBuffer[adr];
}

void classFrame::setHueFromAdress(int adr, int value)
{
    hueBuffer[adr] = value;
}

void classFrame::setSatFromAdress(int adr, int value)
{
    saturationBuffer[adr] = value;
}

void classFrame::setValFromAdress(int adr, int value)
{
    valueBuffer[adr] = value;
}

void classFrame::writeLedsPerPixelsTo(int lesdspixels[])
{
    for (int i = 0; i < frameBufferSize; i++)
    {
        lesdspixels[i] = ledsPerPixel[i];
    }
}

void classFrame::writepixelLedMapTo(int ledsMap[])
{
    for (int i = 0; i < frameBufferSize; i++)
    {
        ledsMap[i] = pixelLedMap[i];
    }
}

classFrame::~classFrame()
{
}
