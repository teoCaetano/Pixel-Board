#ifndef CLASSTRANSITION_H
#define CLASSTRANSITION_H

#include "main.h"

class classTransition
{
    unsigned long timer;
    double count;
    double countValue;
    static double value;
    int speed;
    int type; 
    bool absolut;
public:
    classTransition(int sp, int ty, bool ab );
    double methodValue();
    double methodClock();
};

#endif