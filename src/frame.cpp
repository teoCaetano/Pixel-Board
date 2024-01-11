#include "config.h"
#include "efectos.h"
#include "graphics.h"
#include "main.h"

//-----------------------------------------------------------------------------------------------------------------------------------------
//define the test as true to get the values in the serial monitor
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

//-----------------------------------------------------------------------------------------------------------------------------------------
//arrays initialazaztion
//-----------------------------------------------------------------------------------------------------------------------------------------

int frame2PixelLedMap[FRAME_BUFFER_SIZE];
int ledsPerPixel_prueba[FRAME_BUFFER_SIZE];
int lienzoCartesiano[FRAME_BUFFER_SIZE][2];
int lienzoPoolar[FRAME_BUFFER_SIZE][2];
uint8_t lienzoHue[FRAME_BUFFER_SIZE];
uint8_t lienzoSaturacion[FRAME_BUFFER_SIZE];
uint8_t lienzoValue[FRAME_BUFFER_SIZE];



//-----------------------------------------------------------------------------------------------------------------------------------------
//writes the value array
//-----------------------------------------------------------------------------------------------------------------------------------------
void valueConstructor(int max)
{
  int suma;
  int valorRadios;
  uint8_t valorValor;
  for (int index = 0; index < FRAME_BUFFER_SIZE; index++)
  {
    valorRadios = lienzoPoolar[index][0];
    valorValor = map(valorRadios, 0,max, 0, 255);
    lienzoValue[index] = valorValor;
  }
  if (TEST_VALUE == true)
  {
    for (int i = 0; i < HEIGHT; i++)
    {
      for (int w = 0; w < WIDTH; w++)
      {
        Serial.print("   ");
        Serial.print(lienzoValue[suma]);
        delay(100);
        suma = suma + 1;
      }
      Serial.println(" ");
    }
    delay(500000);
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//writes the saturation to the array
//-----------------------------------------------------------------------------------------------------------------------------------------

void saturacionConstructor(int max)
{
  int suma;
  int valorRadios;
  uint8_t valorSaturacion;
  for (int index = 0; index < FRAME_BUFFER_SIZE; index++)
  {
    valorRadios = lienzoPoolar[index][0];
    valorSaturacion = map(valorRadios, 0, max, 255, 0);
    lienzoSaturacion[index] = valorSaturacion;
  }
  if (TEST_SATURATION == true)
  {
    for (int i = 0; i < HEIGHT; i++)
    {
      for (int w = 0; w < WIDTH; w++)
      {
        Serial.print("   ");
        Serial.print(lienzoSaturacion[suma]);
        delay(100);
        suma = suma + 1;
      }
      Serial.println(" ");
    }
    delay(500000);
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//writes the hue to the array
//-----------------------------------------------------------------------------------------------------------------------------------------

void hueConstructor(uint8_t huemin, uint8_t huemax)
{
  int suma;
  int valorGrados;
  uint8_t valorHue;
  for (int index = 0; index < FRAME_BUFFER_SIZE; index++)
  {
    valorGrados = lienzoPoolar[index][1];
    valorHue = map(valorGrados, 0, 360, hueMin, hueMax);
    lienzoHue[index] = valorHue;
  }
  if (TEST_HUE == true)
  {
    for (int i = 0; i < HEIGHT; i++)
    {
      for (int w = 0; w < WIDTH; w++)
      {
        Serial.print("   ");
        Serial.print(lienzoHue[suma]);
        delay(100);
        suma = suma + 1;
      }
      Serial.println(" ");
    }
    delay(500000);
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//it converts the values of cartesian values to polar and saves them
//-----------------------------------------------------------------------------------------------------------------------------------------

void poolarConstructor(int Y, int X)
{
  double valor_X;
  double valor_Y;
  double radio;
  double angulo;
  int suma;
  Serial.println("                                     ");
  for (int index = 0; index < FRAME_BUFFER_SIZE; index++)
  {
    valor_X = lienzoCartesiano[index][0];
    valor_Y = lienzoCartesiano[index][1];

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

    valor_Y += Y;
    valor_X += X;

    radio = (valor_X * valor_X) + (valor_Y * valor_Y);
    radio = sqrt(radio);

    lienzoPoolar[index][0] = radio;

    angulo = atan2(valor_Y, valor_X);
    angulo = angulo * (180 / PI);

    if (angulo < 0)
    {
      angulo = 360 + angulo;
    }

    lienzoPoolar[index][1] = angulo;
  }
  if (TEST_POOLARES == true)
  {
    for (int i = 0; i < HEIGHT; i++)
    {
      for (int w = 0; w < WIDTH; w++)
      {
        Serial.print("   ");
        Serial.print(lienzoPoolar[suma][0]);
        Serial.print("   ");
        Serial.print(lienzoPoolar[suma][1]);
        delay(100);
        suma = suma + 1;
      }
      Serial.println(" ");
    }
    delay(500000);
  }
}

void cartesianConstructor()
{
  bool restoHeight;
  bool restoWidth;
  int suma;
  Serial.println("                                     ");
  if (HEIGHT % 2 == 1)
  {
    restoHeight = true;
  }
  else
  {
    restoHeight = false;
  }
  if (WIDTH % 2 == 1)
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
    for (int Y = 0; Y < HEIGHT; Y++)
    {
      for (int X = -(WIDTH / 2); X < (WIDTH / 2) + 1; X++)
      {
        lienzoCartesiano[index][0] = X;
        index = index + 1;
      }
    }
  }
  if (restoHeight == true)
  {
    int index = 0;
    for (int Y = -(HEIGHT / 2); Y < (HEIGHT / 2) + 1; Y++)
    {
      for (int X = 0; X < WIDTH; X++)
      {
        lienzoCartesiano[index][1] = Y;
        index = index + 1;
      }
    }
  }
  if (restoWidth == false)
  {
    int index = 0;
    for (int Y = 0; Y < HEIGHT; Y++)
    {
      for (int X = -(WIDTH / 2); X <= (WIDTH / 2); X++)
      {
        if (X == 0)
        {
          X = 1;
        }
        lienzoCartesiano[index][0] = X;
        index = index + 1;
      }
    }
  }
  if (restoHeight == false)
  {
    int index = 0;
    for (int Y = (HEIGHT / 2); Y >= -(HEIGHT / 2); Y--)
    {
      for (int X = 0; X < WIDTH; X++)
      {
        int valueY = Y;
        if (valueY <= 0)
        {
          valueY = valueY - 1;
        }
        lienzoCartesiano[index][1] = valueY;
        index = index + 1;
      }
    }
  }
  if (TEST_CARTESIANO == true)
  {
    for (int i = 0; i < HEIGHT; i++)
    {
      for (int w = 0; w < WIDTH; w++)
      {
        Serial.print("   ");
        Serial.print(lienzoCartesiano[suma][0]);
        Serial.print("   ");
        Serial.print(lienzoCartesiano[suma][1]);
        delay(100);
        suma = suma + 1;
      }
      Serial.println(" ");
    }
    delay(500000);
  }
}

void matrixConstructor(bool serpenty, bool start, bool simetria, int lesdPPixel, bool round)
{
  if (simetria == true)
  {
    int radioMaximo = 0;
    int suma = 0;

    int pixelsPerRow_suma = 0;
    int pixelsPerRow[HEIGHT];
    int pixelsPerRow_value = 0;

    int maxLedsPerRow_resultado = 0;
    int maxLedsPerRow_suma = 0;
    int maxLedsPerRow[HEIGHT];

    Serial.println("                          ");

    /*
      sirve para calcular el radio maximo para el cual quiero calcular los leds
      en caso de round=true utilizo el ancho(WIDHT) para sacar el radio de la circunferencia
      en caso de round=false utilizao el valor del radio poolar del primer pixel del array
    */

    if (round == true)
    {
      radioMaximo = (WIDTH / 2);
    }
    else
    {
      radioMaximo = lienzoPoolar[0][0];
    }

    /*
      utilizo este for para almacenar los valores de la cantidad de pixeles por fila
    */

    for (int Y = 0; Y < HEIGHT; Y++)
    {
      pixelsPerRow_value = 0;
      for (int X = 0; X < WIDTH; X++)
      {
        if (lienzoPoolar[pixelsPerRow_suma][0] <= radioMaximo)
        {
          pixelsPerRow_value = pixelsPerRow_value + 1;
        }
        pixelsPerRow_suma = pixelsPerRow_suma + 1;
      }
      pixelsPerRow[Y] = pixelsPerRow_value;
      if (TEST_PIXELS_PER_ROW == true)
      {
        Serial.println("test pixels per row");
        Serial.println(pixelsPerRow[Y]);
        delay(1000);
      }
    }

    /*
      utilizo este for para sacar el led con mayor denominacio de cada fila
    */

    for (int i = 0; i < HEIGHT; i++)
    {
      maxLedsPerRow_suma += pixelsPerRow[i];
      maxLedsPerRow_resultado = (maxLedsPerRow_suma - 1) * LEDS_PER_PIXEL;
      maxLedsPerRow[i] = maxLedsPerRow_resultado;

      if (TEST_MAX_LEDS_PER_ROW == true)
      {
        Serial.println("test max leds per row");
        Serial.println(maxLedsPerRow_resultado);
        delay(1000);
      }
    }

    for (int i = 0; i < FRAME_BUFFER_SIZE; i++)
    {
      if (lienzoPoolar[i][0] <= radioMaximo)
      {
        ledsPerPixel_prueba[i] = LEDS_PER_PIXEL;
      }
      else
      {
        ledsPerPixel_prueba[i] = 0;
      }
    }

    if (TEST_LEDS_PER_PIXEL == true)
    {
      int suma = 0;
      for (int i = 0; i < HEIGHT; i++)
      {
        for (int w = 0; w < WIDTH; w++)
        {
          Serial.print("   ");
          Serial.print(ledsPerPixel_prueba[suma]);
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
      for (int Y = 0; Y < HEIGHT; Y++)
      {
        valorLed = maxLedsPerRow[Y];
        for (int X = 0; X < WIDTH; X++)
        {
          if (lienzoPoolar[suma][0] <= radioMaximo)
          {
            frame2PixelLedMap[suma] = valorLed;
            valorLed -= LEDS_PER_PIXEL;
          }
          suma += 1;
        }
      }
    }
    if ((serpenty == false) && (start == true)) // no serpenty empieza por la derecha
    {
      int suma = 0;
      int valorLed = 0;
      for (int Y = 0; Y < HEIGHT; Y++)
      {
        for (int X = 0; X < WIDTH; X++)
        {
          if (lienzoPoolar[suma][0] <= radioMaximo)
          {
            frame2PixelLedMap[suma] = valorLed;
            valorLed += LEDS_PER_PIXEL;
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
      for (int Y = 0; Y < HEIGHT; Y++)
      {
        par_impar++;
        if (par_impar % 2 == 1)
        {
          valorLed = maxLedsPerRow[Y];
          for (int X = 0; X < WIDTH; X++)
          {
            if (lienzoPoolar[suma][0] <= radioMaximo)
            {
              frame2PixelLedMap[suma] = valorLed;
              valorLed -= LEDS_PER_PIXEL;
            }
            suma += 1;
          }
        }
        if (par_impar % 2 == 0)
        {
          valorLed = maxLedsPerRow[Y];
          valorLed = valorLed - (pixelsPerRow[Y] * LEDS_PER_PIXEL) + LEDS_PER_PIXEL;
          for (int X = 0; X < WIDTH; X++)
          {
            if (lienzoPoolar[suma][0] <= radioMaximo)
            {
              frame2PixelLedMap[suma] = valorLed;
              valorLed += LEDS_PER_PIXEL;
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
      for (int Y = 0; Y < HEIGHT; Y++)
      {
        par_impar++;
        if (par_impar % 2 == 0)
        {
          valorLed = maxLedsPerRow[Y];
          for (int X = 0; X < WIDTH; X++)
          {
            if (lienzoPoolar[suma][0] <= radioMaximo)
            {
              frame2PixelLedMap[suma] = valorLed;
              valorLed -= LEDS_PER_PIXEL;
            }
            suma += 1;
          }
        }
        if (par_impar % 2 == 1)
        {
          valorLed = maxLedsPerRow[Y];
          valorLed = valorLed - (pixelsPerRow[Y] * LEDS_PER_PIXEL) + LEDS_PER_PIXEL;
          for (int X = 0; X < WIDTH; X++)
          {
            if (lienzoPoolar[suma][0] <= radioMaximo)
            {
              frame2PixelLedMap[suma] = valorLed;
              valorLed += LEDS_PER_PIXEL;
            }
            suma += 1;
          }
        }
      }
    }
    if (TEST_MATRIX == true)
    {
      suma = 0;
      for (int i = 0; i < HEIGHT; i++)
      {
        for (int w = 0; w < WIDTH; w++)
        {
          Serial.print("   ");
          Serial.print(frame2PixelLedMap[suma]);
          delay(100);
          suma = suma + 1;
        }
        Serial.println(" ");
      }
      delay(500000);
    }
  }
  else
  {
    /*
        int frame2PixelLedMap[FRAME_BUFFER_SIZE] = {
      210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,
      195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,
      180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,
      165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,
      150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,
      135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,
      120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,
      105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
      90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104,
      75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
      60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
      45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
      30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
      15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    };

    int ledsPerPixel_prueba [FRAME_BUFFER_SIZE] = {
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    };
    */
  }
}

