#ifndef GRAPHICS_H
#define GRAPHICS_H

void scaleInSteps(int &value, int from, int to, int steps);
void updatePixel(int pixel, int hue, int sat, int val);
void clearFrameBuffer();
void updateLedsTask(void * pvParameters);
void updateLedsSerial();
void updateLeds();

#endif





















