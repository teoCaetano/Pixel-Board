#include <Arduino.h>
#include <FastLED.h>

class classTransition
{
    unsigned long timer;
    float count;
    float countValue;
    float value;
    int speed;
    int type; 
    bool absolut;

    const int MIN = 0;
    const int MAX = 1;

public:
    classTransition(int sp, int ty, bool ab );
    float methodValue();
private:
    float methodClock();
};

classTransition::classTransition(int sp, int ty, bool ab)
{
    speed=sp;
    type=ty; 
    absolut=ab;
}

float classTransition::methodClock()
{
    if (millis()-timer > speed) { 
    count = count + 0.05;
    timer=millis();
    }
    return count;
}


float classTransition::methodValue(){
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
