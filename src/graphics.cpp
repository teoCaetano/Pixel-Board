#include "efectos.h"
#include "graphics.h"
#include "config.h"
#include "main.h"
#include "frame.h"


CHSVPalette16 prueba1(
  CHSV(0,230,250),
  CHSV(20,230,250),
  CHSV(40,230,250),
  CHSV(60,230,250),
  CHSV(80,230,250),
  CHSV(100,230,250),
  CHSV(120,230,250),
  CHSV(140,230,250),
  CHSV(160,230,250),
  CHSV(180,230,250),
  CHSV(200,230,250),
  CHSV(220,230,250),
  CHSV(240,230,250),
  CHSV(0,100,250),
  CHSV(20,30,250),
  CHSV(40,0,250)
);

CHSVPalette16 prueba3(
  CHSV(255,230,250),
  CHSV(0,230,250),
  CHSV(0,230,250),
  CHSV(0,230,250),
  CHSV(20,230,250),
  CHSV(20,230,250),
  CHSV(30,0,250),
  CHSV(40,230,250),
  CHSV(40,230,250),
  CHSV(30,230,250),
  CHSV(20,230,250),
  CHSV(20,230,250),
  CHSV(0,230,250),
  CHSV(0,230,250),
  CHSV(0,230,250),
  CHSV(255,230,250)
);

CHSV prueba2;


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
      /*
      leds[pixelLed] = CHSV(h,s,v);
      leds[pixelLed+1] = CHSV(h,s,v);
      leds[pixelLed+2] = CHSV(h,s,v);      
      */
      if (true)
      {
      prueba2 = ColorFromPalette(prueba1, h,250,LINEARBLEND);
      leds[pixelLed] = CHSV(prueba2.hue,s,v);
      leds[pixelLed+1] = CHSV(prueba2.hue,s,v);
      leds[pixelLed+2] = CHSV(prueba2.hue,s,v);
      }
      else{
      prueba2 = ColorFromPalette(prueba1, h,250,LINEARBLEND);
      leds[pixelLed] = prueba2;
      leds[pixelLed+1] = prueba2;
      leds[pixelLed+2] = prueba2;
      }
      

    }
  }
  if (newBr != br) {
    br=newBr;
    FastLED.setBrightness(br);
  }
  FastLED.show();
}
