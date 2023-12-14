#include <Arduino.h>
#include <FastLED.h>

class classTransition
{
    unsigned long timer;
    double count;
    double countValue;
    double value;
    int speed;
    int type; 
    bool absolut;
public:
    classTransition(int sp, int ty, bool ab );
    double methodValue();
    double methodClock();
};

classTransition::classTransition(int sp, int ty, bool ab)
{
    speed=sp;
    type=ty; 
    absolut=ab;
}

double classTransition::methodClock()
{
    if (millis()-timer > speed) { 
    count = count + 0.05;
    timer=millis();
    }
    return count;
}

double classTransition::methodValue(){
    countValue=methodClock();
    switch (type)
    {
    case 1:
        value = sin(countValue);
        break;
    case 2:
        value = (sin(countValue/3)+cos(countValue*2))/2;
        break;
    case 3:
        value = sin(tan(countValue));
        break;
    case 4:
        value = (sin(countValue)/3) + 0.6;
        break;
    case 5:
        value = ((sin(countValue/2)*cos(countValue))+1)/2;
        break;
    case 6:
        value = (sin(countValue)+cos(countValue/5))/3 + 0.5;
    break;            
    default:
        value = 1;
        break;
  }
  //defines if the color trasition is te absolute or just the positives
  if (absolut == true)
  {
    value = abs(value);
  }
  if (absolut == false)
  {
    if (value < 0)
    {
      value = 0;
    }
  }
  if (value > 1)
  {
    value = 1;
  }
  return value;
}