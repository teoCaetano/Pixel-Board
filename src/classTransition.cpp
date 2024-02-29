#include <Arduino.h>
#include <FastLED.h>
#include <vector>
#include <algorithm>
#include "classFrame.h"
#include "classArco.h"
#include "classAlma.h"
#include "graphics.h"



class classTransition
{
private:
    classFrame &objetoFrame;
    classAlma &objetoAlma;

    int valToResize = 11;
    int globalSteps = 10;

    std::vector<int> mem_sat_ring_10= {25,   45,  65, 100, 140, 200, 200, 100,  65,  45,  25};
    std::vector<int> mem_sat_ring_9 = {45,   65, 100, 140, 200, 210, 210, 140, 100,  65,  45};
    std::vector<int> mem_sat_ring_8 = {65,  100, 140, 200, 210, 215, 210, 200, 140, 100,  65};
    std::vector<int> mem_sat_ring_7 = {100, 140, 200, 210, 215, 215, 215, 210, 200, 140, 100};
    std::vector<int> mem_sat_ring_6 = {140, 200, 210, 215, 215,   0, 215, 215, 210, 200, 140};
    std::vector<int> mem_sat_ring_5 = {200, 215, 215, 215,   0,   0,   0, 215, 215, 215, 200};
    std::vector<int> mem_sat_ring_4 = {215, 215, 215,   0,   0,   0,   0,   0, 215, 215, 215};
    std::vector<int> mem_sat_ring_3 = {215, 215,   0,   0,   0,   0,   0,   0,   0, 215, 215};
    std::vector<int> mem_sat_ring_2 = {215,   0,   0,   0,   0,   0,   0,   0,   0,   0, 215};
    std::vector<int> mem_sat_ring_1 = {0 ,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0};

    std::vector<int> mem_val_ring_10 = {250, 250, 245, 225, 200, 140, 200, 225, 245, 250, 250};
    std::vector<int> mem_val_ring_9 = {250, 245,  225, 200, 140, 100, 140, 200, 225, 245, 250};
    std::vector<int> mem_val_ring_8 = {245, 225,  200, 140, 100,  50, 100, 140, 200, 225, 245};
    std::vector<int> mem_val_ring_7 = {225, 200,  140, 100,  50,  10,  50, 100, 140, 200, 225};
    std::vector<int> mem_val_ring_6 = {200, 140,  100,  50,  10,   0,  10,  50, 100, 140, 200};
    std::vector<int> mem_val_ring_5 = {140, 100,   50,  10,   0,   0,   0,  10,  50, 100, 140};
    std::vector<int> mem_val_ring_4 = {100,  50,   10,   0,   0,   0,   0,   0,  10,  50, 100};
    std::vector<int> mem_val_ring_3 = {50,   10,    0,   0,   0,   0,   0,   0,   0,  10,  50};
    std::vector<int> mem_val_ring_2 = {10,    0,    0,   0,   0,   0,   0,   0,   0,   0,  10};
    std::vector<int> mem_val_ring_1 = {0,     0,    0,   0,   0,   0,   0,   0,   0,   0,   0};


public:
    classTransition(classFrame &algoo, classAlma &alma);
    void showFillallIn(int frame);
};

classTransition::classTransition(classFrame &algoo, classAlma &alma) : objetoFrame(algoo), objetoAlma(alma) {}

void classTransition::showFillallIn(int frame)
{
    static int act_val_ring_10 = mem_val_ring_10[0];
    static int act_val_ring_9 = mem_val_ring_9[0];
    static int act_val_ring_8 = mem_val_ring_8[0];
    static int act_val_ring_7 = mem_val_ring_7[0];
    static int act_val_ring_6 = mem_val_ring_6[0];
    static int act_val_ring_5 = mem_val_ring_5[0];
    static int act_val_ring_4 = mem_val_ring_4[0];
    static int act_val_ring_3 = mem_val_ring_3[0];
    static int act_val_ring_2 = mem_val_ring_2[0];
    static int act_val_ring_1 = mem_val_ring_1[0];

    static int act_sat_ring_10 = mem_sat_ring_10[0];
    static int act_sat_ring_9 = mem_sat_ring_9[0];
    static int act_sat_ring_8 = mem_sat_ring_8[0];
    static int act_sat_ring_7 = mem_sat_ring_7[0];
    static int act_sat_ring_6 = mem_sat_ring_6[0];
    static int act_sat_ring_5 = mem_sat_ring_5[0];
    static int act_sat_ring_4 = mem_sat_ring_4[0];
    static int act_sat_ring_3 = mem_sat_ring_3[0];
    static int act_sat_ring_2 = mem_sat_ring_2[0];
    static int act_sat_ring_1 = mem_sat_ring_1[0];

    static int mem_frame = 0;
    static int act_frame = 0;
    if ((frame >= 1) && (frame <= 10))
    {
        if (act_frame != frame)
        {
            mem_frame = act_frame;
            act_frame = frame;

            act_sat_ring_10 = mem_sat_ring_10[mem_frame];
            act_val_ring_10 = mem_val_ring_10[mem_frame];

            act_sat_ring_9 = mem_sat_ring_9[mem_frame];
            act_val_ring_9 = mem_val_ring_9[mem_frame];

            act_sat_ring_8 = mem_sat_ring_8[mem_frame];
            act_val_ring_8 = mem_val_ring_8[mem_frame];

            act_sat_ring_7 = mem_sat_ring_7[mem_frame];
            act_val_ring_7 = mem_val_ring_7[mem_frame];

            act_sat_ring_6 = mem_sat_ring_6[mem_frame];
            act_val_ring_6 = mem_val_ring_6[mem_frame];

            act_sat_ring_5 = mem_sat_ring_5[mem_frame];
            act_val_ring_5 = mem_val_ring_5[mem_frame];

            act_sat_ring_4 = mem_sat_ring_4[mem_frame];
            act_val_ring_4 = mem_val_ring_4[mem_frame];

            act_sat_ring_3 = mem_sat_ring_3[mem_frame];
            act_val_ring_3 = mem_val_ring_3[mem_frame];

            act_sat_ring_2 = mem_sat_ring_2[mem_frame];
            act_val_ring_2 = mem_val_ring_2[mem_frame];

            act_sat_ring_1 = mem_sat_ring_1[mem_frame];
            act_val_ring_1 = mem_val_ring_1[mem_frame];
        }

        Serial.println(frame);

        scaleInSteps(act_sat_ring_10, mem_sat_ring_10[mem_frame], mem_sat_ring_10[act_frame], globalSteps);
        scaleInSteps(act_val_ring_10, mem_val_ring_10[mem_frame], mem_val_ring_10[act_frame], globalSteps);

        scaleInSteps(act_sat_ring_9, mem_sat_ring_9[mem_frame], mem_sat_ring_9[act_frame], globalSteps);
        scaleInSteps(act_val_ring_9, mem_val_ring_9[mem_frame], mem_val_ring_9[act_frame], globalSteps);

        scaleInSteps(act_sat_ring_8, mem_sat_ring_8[mem_frame], mem_sat_ring_8[act_frame], globalSteps);
        scaleInSteps(act_val_ring_8, mem_val_ring_8[mem_frame], mem_val_ring_8[act_frame], globalSteps);

        scaleInSteps(act_sat_ring_7, mem_sat_ring_7[mem_frame], mem_sat_ring_7[act_frame], globalSteps);
        scaleInSteps(act_val_ring_7, mem_val_ring_7[mem_frame], mem_val_ring_7[act_frame], globalSteps);

        scaleInSteps(act_sat_ring_6, mem_sat_ring_6[mem_frame], mem_sat_ring_6[act_frame], globalSteps);
        scaleInSteps(act_val_ring_6, mem_val_ring_6[mem_frame], mem_val_ring_6[act_frame], globalSteps);

        scaleInSteps(act_sat_ring_5, mem_sat_ring_5[mem_frame], mem_sat_ring_5[act_frame], globalSteps);
        scaleInSteps(act_val_ring_5, mem_val_ring_5[mem_frame], mem_val_ring_5[act_frame], globalSteps);

        scaleInSteps(act_sat_ring_4, mem_sat_ring_4[mem_frame], mem_sat_ring_4[act_frame], globalSteps);
        scaleInSteps(act_val_ring_4, mem_val_ring_4[mem_frame], mem_val_ring_4[act_frame], globalSteps);

        scaleInSteps(act_sat_ring_3, mem_sat_ring_3[mem_frame], mem_sat_ring_3[act_frame], globalSteps);
        scaleInSteps(act_val_ring_3, mem_val_ring_3[mem_frame], mem_val_ring_3[act_frame], globalSteps);

        scaleInSteps(act_sat_ring_2, mem_sat_ring_2[mem_frame], mem_sat_ring_2[act_frame], globalSteps);
        scaleInSteps(act_val_ring_2, mem_val_ring_2[mem_frame], mem_val_ring_2[act_frame], globalSteps);

        scaleInSteps(act_sat_ring_1, mem_sat_ring_1[mem_frame], mem_sat_ring_1[act_frame], globalSteps);
        scaleInSteps(act_val_ring_1, mem_val_ring_1[mem_frame], mem_val_ring_1[act_frame], globalSteps);

        objetoAlma.setAlmaRingTo(objetoAlma.saturationEffecto, 10, act_sat_ring_10);
        objetoAlma.setAlmaRingTo(objetoAlma.valueEffecto, 10, act_val_ring_10);

        objetoAlma.setAlmaRingTo(objetoAlma.saturationEffecto, 9, act_sat_ring_9);
        objetoAlma.setAlmaRingTo(objetoAlma.valueEffecto, 9, act_val_ring_9);

        objetoAlma.setAlmaRingTo(objetoAlma.saturationEffecto, 8, act_sat_ring_8);
        objetoAlma.setAlmaRingTo(objetoAlma.valueEffecto, 8, act_val_ring_8);

        objetoAlma.setAlmaRingTo(objetoAlma.saturationEffecto, 7, act_sat_ring_7);
        objetoAlma.setAlmaRingTo(objetoAlma.valueEffecto, 7, act_val_ring_7);

        objetoAlma.setAlmaRingTo(objetoAlma.saturationEffecto, 6, act_sat_ring_6);
        objetoAlma.setAlmaRingTo(objetoAlma.valueEffecto, 6, act_val_ring_6);

        objetoAlma.setAlmaRingTo(objetoAlma.saturationEffecto, 5, act_sat_ring_5);
        objetoAlma.setAlmaRingTo(objetoAlma.valueEffecto, 5, act_val_ring_5);

        objetoAlma.setAlmaRingTo(objetoAlma.saturationEffecto, 4, act_sat_ring_4);
        objetoAlma.setAlmaRingTo(objetoAlma.valueEffecto, 4, act_val_ring_4);

        objetoAlma.setAlmaRingTo(objetoAlma.saturationEffecto, 3, act_sat_ring_3);
        objetoAlma.setAlmaRingTo(objetoAlma.valueEffecto, 3, act_val_ring_3);

        objetoAlma.setAlmaRingTo(objetoAlma.saturationEffecto, 2, act_sat_ring_2);
        objetoAlma.setAlmaRingTo(objetoAlma.valueEffecto, 2, act_val_ring_2);

        objetoAlma.setAlmaRingTo(objetoAlma.saturationEffecto, 1, act_sat_ring_1);
        objetoAlma.setAlmaRingTo(objetoAlma.valueEffecto, 1, act_val_ring_1);
    }
}
