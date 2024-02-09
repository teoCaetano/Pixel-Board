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


/*
    @brief true if the leds are wired serpenty like an S
*/
#define SERPENTY true
/*
    @brief true if first led is at the right false if left
*/
#define START_LOCATION false
/*
    @brief keep at 1 if if your pixels are 1 led, and 2 if the pixels are 2, and so on forth
*/
#define LEDS_PER_PIXEL 3
/*
    @brief false if your matrix is custom
*/
#define SYMETRIC true
/*
    @brief true if your matrix is circle shaped
*/
#define ROUND_MATRIX true


#define LED_PIN     23

#define COLOR_ORDER GRB
#define CHIPSET     WS2812
/*
* @brief max Brigthness of the system
 If you have twinkle in the leds, maybe you have to increase the BRIGTHNESS variable
*/
#define BRIGHTNESS  50

#define HEIGHT 20 // Y axis
#define WIDTH 20 // X axis 
#define FRAME_BUFFER_SIZE HEIGHT*WIDTH
#define NUM_LEDS    FRAME_BUFFER_SIZE*3

#define hueMin 0
#define hueMax 255



#endif
