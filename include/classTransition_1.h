#ifndef CLASSTRANSITION_1_H
#define CLASSTRANSITION_1_H

#include <vector>
#include <algorithm>
#include "classFrame.h"
#include "classAlma.h"
#include "classArco.h"

class classTransition1
{
private:
    classFrame &objetoFrame;
    classAlma &objetoAlma;
    int valToResize = 11;
    int globalSteps = 5;


    std::vector<int> mem_sat_ring_10= {25,   45,  65, 100, 140, 200, 200, 100,  65,  45,  25};
    std::vector<int> mem_sat_ring_9 = {45,   65, 100, 140, 200, 210, 210, 140, 100,  65,  45};
    std::vector<int> mem_sat_ring_8 = {65,  100, 140, 200, 210, 215, 210, 200, 140, 100,  65};
    std::vector<int> mem_sat_ring_7 = {100, 140, 200, 210, 215, 215, 215, 210, 200, 140, 100};
    std::vector<int> mem_sat_ring_6 = {140, 200, 210, 215, 215,   0, 215, 215, 210, 200, 140};
    std::vector<int> mem_sat_ring_5 = {200, 215, 215, 215,   0,   0,   0, 215, 215, 215, 200};
    std::vector<int> mem_sat_ring_4 = {215, 215, 215,   0,   0,   0,   0,   0, 215, 215, 215};
    std::vector<int> mem_sat_ring_3 = {215, 215,   0,   0,   0,   0,   0,   0,   0, 215, 200};
    std::vector<int> mem_sat_ring_2 = {215,   0,   0,   0,   0,   0,   0,   0,   0,   0, 200};
    std::vector<int> mem_sat_ring_1 = {0 ,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0};

    std::vector<int> mem_val_ring_10 = {250, 250, 245, 225, 200, 140, 200, 225, 215, 215, 250};
    std::vector<int> mem_val_ring_9 = {250, 245,  225, 200, 140, 100, 140, 200, 215, 215, 250};
    std::vector<int> mem_val_ring_8 = {245, 225,  200, 140, 100,  50, 100, 140, 215, 215, 245};
    std::vector<int> mem_val_ring_7 = {225, 200,  140, 100,  50,  10,  50, 100, 215, 215, 225};
    std::vector<int> mem_val_ring_6 = {200, 140,  100,  50,  10,   0,  10,  50, 215, 215, 200};
    std::vector<int> mem_val_ring_5 = {140, 100,   50,  10,   0,   0,   0,  10, 215, 215, 140};
    std::vector<int> mem_val_ring_4 = {100,  50,   10,   0,   0,   0,   0,   0,  10, 215, 100};
    std::vector<int> mem_val_ring_3 = {50,   10,    0,   0,   0,   0,   0,   0,   0,  10,  50};
    std::vector<int> mem_val_ring_2 = {10,    0,    0,   0,   0,   0,   0,   0,   0,   0,  10};
    std::vector<int> mem_val_ring_1 = {0,     0,    0,   0,   0,   0,   0,   0,   0,   0,   0};

    int act_val_ring_10 = mem_val_ring_10[0];
    int act_val_ring_9 = mem_val_ring_9[0];
    int act_val_ring_8 = mem_val_ring_8[0];
    int act_val_ring_7 = mem_val_ring_7[0];
    int act_val_ring_6 = mem_val_ring_6[0];
    int act_val_ring_5 = mem_val_ring_5[0];
    int act_val_ring_4 = mem_val_ring_4[0];
    int act_val_ring_3 = mem_val_ring_3[0];
    int act_val_ring_2 = mem_val_ring_2[0];
    int act_val_ring_1 = mem_val_ring_1[0];

    int act_sat_ring_10 = mem_sat_ring_10[0];
    int act_sat_ring_9 = mem_sat_ring_9[0];
    int act_sat_ring_8 = mem_sat_ring_8[0];
    int act_sat_ring_7 = mem_sat_ring_7[0];
    int act_sat_ring_6 = mem_sat_ring_6[0];
    int act_sat_ring_5 = mem_sat_ring_5[0];
    int act_sat_ring_4 = mem_sat_ring_4[0];
    int act_sat_ring_3 = mem_sat_ring_3[0];
    int act_sat_ring_2 = mem_sat_ring_2[0];
    int act_sat_ring_1 = mem_sat_ring_1[0];

    int mem_frame = 0;
    int act_frame = 0;

public:
    classTransition1(classFrame &algoo, classAlma &alma);
    void showFillallIn(int frame);
};





#endif