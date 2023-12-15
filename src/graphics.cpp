#include "efectos.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "frame.h"

int getBufferIndex(int x, int y) {
  return (y*20+x);
}

void clearFrameBuffer() {
  for (int n=0; n<FRAME_BUFFER_SIZE; n++) {
    frameBuffer[n][0]=0;
    frameBuffer[n][1]=0;
    frameBuffer[n][2]=0;
  }
}



void updateLedsTask(void * pvParameters) {
  Serial.print ("STARTING VIDEO TASK ON CORE: ");
  Serial.println (xPortGetCoreID());
  while (1) {
    updateLeds();
    //delay (1);
  }
}

void updateLedsSerial() {
  for (int n=0; n<FRAME_BUFFER_SIZE; n++) {
    int pixelLed=frame2PixelLedMap[n];
    if (pixelLed > -1)  {
      uint8_t h=frameBuffer[n][0];
      uint8_t s=frameBuffer[n][1];
      uint8_t v=frameBuffer[n][2];
      leds[pixelLed] = CHSV(h,s,v);
      leds[pixelLed+1] = CHSV(h,s,v);
      leds[pixelLed+2] = CHSV(h,s,v);
      Serial.printf ("%d,%d,%d;", leds[pixelLed].r, leds[pixelLed].g, leds[pixelLed].b);
    }
    else
      Serial.print ("0,0,0;");
  
  }
  Serial.println();
}


void updateLeds() {
  for (int n=0; n<FRAME_BUFFER_SIZE; n++) {
    int pixelLed=frame2PixelLedMap[n];
    if (pixelLed > -1)  {
      uint8_t h=frameBuffer[n][0];
      uint8_t s=frameBuffer[n][1];
      uint8_t v=frameBuffer[n][2];
      leds[pixelLed] = CHSV(h,s,v);
      leds[pixelLed+1] = CHSV(h,s,v);
      leds[pixelLed+2] = CHSV(h,s,v);
    }
  }
  if (newBr != br) {
    br=newBr;
    FastLED.setBrightness(br);
  }
  FastLED.show();
}
