#ifndef CLASSTRANSITION_H
#define CLASSTRANSITION_H

#include "main.h"

class classTransition
{
    unsigned long timer;
    float count;
    float countValue;
    float value;
    int speed;
    int type; 
    bool absolut;

    const int MIN ;
    const int MAX ;

public:
    classTransition(int sp, int ty, bool ab );
    float methodValue();
private:
    float methodClock();
};





#endif