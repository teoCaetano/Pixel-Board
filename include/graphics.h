#ifndef GRAPHICS_H
#define GRAPHICS_H

int getBufferIndex(int x, int y);
void clearFrameBuffer();
void updateLedsTask(void * pvParameters);
void updateLedsSerial();
void updateLeds();

#endif





















