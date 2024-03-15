#include <Arduino.h>
#include <FastLED.h>
#include "config.h"
#include "Debug_tools.h"
#include "efecto_1.h"
#include "efecto_2.h"
#include "efecto_3.h"
#include "efecto_4.h"
#include "efecto_5.h"
#include "efecto_6.h"
#include "efecto_7.h"
#include "efecto_8.h"
#include "graphics.h"
#include "main.h"
#include "classFrame.h"
#include "FastNoiseLite.h"
#include "classAlma.h"

int br = BRIGHTNESS;
int newBr = br;
int sp = 9;

CRGB leds[NUM_LEDS];
uint8_t frameBuffer[FRAME_BUFFER_SIZE][3];

/*
  @brief en caso de no poder usar matrixConstructor para generar los mapas de los leds,
  inicializar los arrays frame2PixelLedMap y ledsPerPixel_prueba a los valores de la matriz
*/

int ledsPerPixel_prueba[FRAME_BUFFER_SIZE];

int frame2PixelLedMap[FRAME_BUFFER_SIZE] = { 
 -1,  -1,  -1,  -1,  -1,  -1,  -1,  15,  12,   9,   6,   3,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
 -1,  -1,  -1,  -1,  -1,  18,  21,  24,  27,  30,  33,  36,  39,  42,  45,  -1,  -1,  -1,  -1,  -1,
 -1,  -1,  -1,  87,  84,  81,  78,  75,  72,  69,  66,  63,  60,  57,  54,  51,  48,  -1,  -1,  -1,
 -1,  -1,  90,  93,  96,  99, 102, 105, 108, 111, 114, 117, 120, 123, 126, 129, 132, 135,  -1,  -1,
 -1,  -1, 183, 180, 177, 174, 171, 168, 165, 162, 159, 156, 153, 150, 147, 144, 141, 138,  -1,  -1,
 -1, 186, 189, 192, 195, 198, 201, 204, 207, 210, 213, 216, 219, 222, 225, 228, 231, 234, 237,  -1,
 -1, 291, 288, 285, 282, 279, 276, 273, 270, 267, 264, 261, 258, 255, 252, 249, 246, 243, 240,  -1,
294, 297, 300, 303, 306, 309, 312, 315, 318, 321, 324, 327, 330, 333, 336, 339, 342, 345, 348, 351,
411, 408, 405, 402, 399, 396, 393, 390, 387, 384, 381, 378, 375, 372, 369, 366, 363, 360, 357, 354,
414, 417, 420, 423, 426, 429, 432, 435, 438, 441, 444, 447, 450, 453, 456, 459, 462, 465, 468, 471,
531, 528, 525, 522, 519, 516, 513, 510, 507, 504, 501, 498, 495, 492, 489, 486, 483, 480, 477, 474,
534, 537, 540, 543, 546, 549, 552, 555, 558, 561, 564, 567, 570, 573, 576, 579, 582, 585, 588, 591,
651, 648, 645, 642, 639, 636, 633, 630, 627, 624, 621, 618, 615, 612, 609, 606, 603, 600, 597, 594, 
 -1, 654, 657, 660, 663, 666, 669, 672, 675, 678, 681, 684, 687, 690, 693, 696, 699, 702, 705,  -1,
 -1, 759, 756, 753, 750, 747, 744, 741, 738, 735, 732, 729, 726, 723, 720, 717, 714, 711, 708,  -1,
 -1,  -1, 762, 765, 768, 771, 774, 777, 780, 783, 786, 789, 792, 795, 798, 801, 804, 807,  -1,  -1,
 -1,  -1, 855, 852, 849, 846, 843, 840, 837, 834, 831, 828, 825, 822, 819, 816, 813, 810,  -1,  -1,
 -1,  -1,  -1, 858, 861, 864, 867, 870, 873, 876, 879, 882, 885, 888, 891, 894, 897,  -1,  -1,  -1,
 -1,  -1,  -1,  -1,  -1, 927, 924, 921, 918, 915, 912, 909, 906, 903, 900,  -1,  -1,  -1,  -1,  -1,
 -1,  -1,  -1,  -1,  -1,  -1,  -1, 930, 933, 936, 939, 942, 945,  -1,  -1,  -1,  -1,  -1,  -1,  -1};

/*
int frame2PixelLedMap[FRAME_BUFFER_SIZE] = {
    -1, -1, -1, -1, -1, -1, 0, 1, 4, 7, 10, 13, 16, 19, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, 20, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, -1, -1, -1, -1,
    -1, -1, -1, 52, 53, 56, 59, 62, 65, 68, 71, 74, 77, 80, 83, 86, 89, -1, -1, -1,
    -1, -1, 90, 91, 94, 97, 100, 103, 106, 109, 112, 115, 118, 121, 124, 127, 130, 133, -1, -1,
    -1, 134, 135, 138, 141, 144, 147, 150, 153, 156, 159, 162, 165, 168, 171, 174, 177, 180, 183, -1,
    -1, 184, 186, 189, 192, 195, 198, 201, 204, 207, 210, 213, 216, 219, 222, 225, 228, 231, 234, -1,
    236, 237, 240, 243, 246, 249, 252, 255, 258, 261, 264, 267, 270, 273, 276, 279, 282, 285, 288, 291,
    292, 293, 296, 299, 302, 305, 308, 311, 314, 317, 320, 323, 326, 329, 332, 335, 338, 341, 344, 347,
    348, 350, 353, 356, 359, 362, 365, 368, 371, 374, 377, 380, 383, 386, 389, 392, 395, 398, 401, 404,
    406, 408, 411, 414, 417, 420, 423, 426, 429, 432, 435, 438, 441, 444, 447, 450, 453, 456, 459, 462,
    464, 466, 469, 472, 475, 478, 481, 484, 487, 490, 493, 496, 499, 502, 505, 508, 511, 514, 517, 520,
    522, 524, 527, 530, 533, 536, 539, 542, 545, 548, 551, 554, 557, 560, 563, 566, 569, 572, 575, 578,
    580, 581, 584, 587, 590, 593, 596, 599, 602, 605, 608, 611, 614, 617, 620, 623, 626, 629, 632, 635,
    636, 637, 640, 643, 646, 649, 652, 655, 658, 661, 664, 667, 670, 673, 676, 679, 682, 685, 688, 691,
    -1, 692, 694, 697, 700, 703, 706, 709, 712, 715, 718, 721, 724, 727, 730, 733, 736, 739, 742, -1,
    -1, 744, 745, 748, 751, 754, 757, 760, 763, 766, 769, 772, 775, 778, 781, 784, 787, 790, 793, -1,
    -1, -1, 794, 795, 798, 801, 804, 807, 810, 813, 816, 819, 822, 825, 828, 831, 834, 837, -1, -1,
    -1, -1, -1, 838, 839, 842, 845, 848, 851, 854, 857, 860, 863, 866, 869, 872, 875, -1, -1, -1,
    -1, -1, -1, -1, 876, 877, 880, 883, 886, 889, 892, 895, 898, 901, 904, 907, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 908, 909, 912, 915, 918, 921, 924, 927, -1, -1, -1, -1, -1, -1

};

int ledsPerPixel_prueba[FRAME_BUFFER_SIZE] = {
    -1, -1, -1, -1, -1, -1, 1, 3, 3, 3, 3, 3, 3, 1, -1, -1, -1, -1, -1, -1, // R3
    -1, -1, -1, -1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, -1, -1, -1, -1,     // R3
    -1, -1, -1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, -1, -1, -1,       // R1
    -1, -1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, -1, -1,         // R1
    -1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, -1,           // R3
    -1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, -1,           // R2
    1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1,             // R3
    1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1,             // R1
    2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2,             // R2
    2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2,             // R2
    2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2,             // R2
    2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2,             // R2
    1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1,             // R1
    1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1,             // R3
    -1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, -1,           // R2
    -1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, -1,           // R3
    -1, -1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, -1, -1,         // R1
    -1, -1, -1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, -1, -1, -1,       // R1
    -1, -1, -1, -1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, -1, -1, -1, -1,     // R3
    -1, -1, -1, -1, -1, -1, 1, 3, 3, 3, 3, 3, 3, 2, -1, -1, -1, -1, -1, -1  // R3
};
*/


// objetos globales

classFrame algoo(HEIGHT, WIDTH);
classAlma alma1(algoo);

FastNoiseLite noise;
FastNoiseLite noise2;

enum Efectos Efecto = EFECTO3;

void initEfectos();

void setup()
{

  Serial.begin(115200);
  algoo.constructorXY();
  algoo.constructorPolar();
  algoo.constructorMapDegre();

  /*
    commentar estos 3 metodos de algo en caso de no usar matrix constructor para generar los mapas de la matriz
  */
  algoo.matrixConstructor(SERPENTY, START_LOCATION, SYMETRIC, 3, ROUND_MATRIX);
  algoo.writeLedsPerPixelsTo(ledsPerPixel_prueba);
  //algoo.writepixelLedMapTo(frame2PixelLedMap);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(br);
  FastLED.clear();
  FastLED.show(); // display this frame
  noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
  noise2.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
  noise2.SetSeed(1231);
  delay(200);
  clearFrameBuffer();
  xTaskCreatePinnedToCore(
      updateLedsTask,   /* Function to implement the task */
      "updateLedsTask", /* Name of the task */
      10000,            /* Stack size in words */
      NULL,             /* Task input parameter */
      0,                /* Priority of the task */
      NULL,             /* Task handle. */
      0);               /* Core where the task should run */
  Serial.println("START!");
}

void loop()
{
  switch (Efecto)
  {
  case NINGUNO:
    Serial.println("DEBUG");
    DebugFrame();
    break;
  case EFECTO1:
    Serial.println("efecto 1");
    efecto1();
    break;
  case EFECTO2:
    Serial.println("efecto 2");
    efecto2();
    break;
  case EFECTO3:
    Serial.println("efecto 3");
    efecto3();
    break;
  case EFECTO4:
    Serial.println("efecto 4");
    efecto4();
  case EFECTO5:
    Serial.println("efecto 5");
    efecto5();
  case EFECTO6:
    Serial.println("efecto 6");
    efecto6();
  case EFECTO7:
    Serial.println("efecto 7");
    efecto7();
  case EFECTO8:
    Serial.println("efecto 8");
    efecto8();
    break;
  default:
    break;
  }
}

void serialCheck()
{
  if (Serial.available())
  {
    char ch = Serial.read();
    Serial.println(ch);
    if (ch == '+')
      subirSpeed();
    else if (ch == '-')
      bajarSpeed();
    else if (ch == 'q')
      subirBrillo();
    else if (ch == 'a')
      bajarBrillo();
    else if (ch == '1')
      Efecto = EFECTO1;
    else if (ch == '2')
      Efecto = EFECTO2;
    else if (ch == '3')
      Efecto = EFECTO3;
    else if (ch == '4')
      Efecto = EFECTO4;
    else if (ch == '5')
      Efecto = EFECTO5;
    else if (ch == '6')
      Efecto = EFECTO6;
    else if (ch == '7')
      Efecto = EFECTO7;
    else if (ch == '8')
      Efecto = EFECTO8;
  }
}

void subirSpeed()
{
  sp -= 1;
  if (sp < 0)
    sp = 0;
  Serial.print("SP: ");
  Serial.println(sp);
}
void bajarSpeed()
{
  sp += 1;
  if (sp > 10)
    sp = 10;
  Serial.print("SP: ");
  Serial.println(sp);
}

void subirBrillo()
{
  int b = newBr + 10;
  if (b > BRIGHTNESS)
    b = BRIGHTNESS;
  newBr = b;
}

void bajarBrillo()
{
  int b = newBr - 10;
  if (b < 10)
    b = 10;
  newBr = b;
}

void initEfectos()
{
  alma1.setAlmaRingTo(alma1.valueEffecto, 11, 255);
  alma1.setAlmaRingTo(alma1.valueEffecto, 10, 255);
  alma1.setAlmaRingTo(alma1.valueEffecto, 9, 250);
  alma1.setAlmaRingTo(alma1.valueEffecto, 8, 245);
  alma1.setAlmaRingTo(alma1.valueEffecto, 7, 225);
  alma1.setAlmaRingTo(alma1.valueEffecto, 6, 200);
  alma1.setAlmaRingTo(alma1.valueEffecto, 5, 140);
  alma1.setAlmaRingTo(alma1.valueEffecto, 4, 100);
  alma1.setAlmaRingTo(alma1.valueEffecto, 3, 50);
  alma1.setAlmaRingTo(alma1.valueEffecto, 2, 10);
  alma1.setAlmaRingTo(alma1.valueEffecto, 1, 0);

  alma1.setAlmaRingTo(alma1.saturationEffecto, 11, 25);
  alma1.setAlmaRingTo(alma1.saturationEffecto, 10, 25);
  alma1.setAlmaRingTo(alma1.saturationEffecto, 9, 45);
  alma1.setAlmaRingTo(alma1.saturationEffecto, 8, 65);
  alma1.setAlmaRingTo(alma1.saturationEffecto, 7, 100);
  alma1.setAlmaRingTo(alma1.saturationEffecto, 6, 140);
  alma1.setAlmaRingTo(alma1.saturationEffecto, 5, 200);
  alma1.setAlmaRingTo(alma1.saturationEffecto, 4, 215);
  alma1.setAlmaRingTo(alma1.saturationEffecto, 3, 180);
  alma1.setAlmaRingTo(alma1.saturationEffecto, 2, 180);
  alma1.setAlmaRingTo(alma1.saturationEffecto, 1, 0);
}