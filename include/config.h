#ifndef CONFIG_H
#define CONFIG_H

// CONSUMOS
// BR=255
// 10 Leds = 363 Ma
// 20 Leds = 653
// 30 Leds = 950

// BR=127
// 10 Leds = 210 mA
// 20 Leds = 355 mA
// 30 Leds = 503 mA


#define LED_PIN     23
#define pRFDATA 32
#define pBTN  27

#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define NUM_LEDS    474*2
#define BRIGHTNESS  70

#define NUM_EFECTOS 8
#define FRAME_BUFFER_SIZE 400     //20 x 20

#define hueMin 0
#define hueMax 255



#endif
