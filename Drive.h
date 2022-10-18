
#include <Arduino.h>
#ifndef DRIVE_H
#define DRIVE_H
#include "Drive.h"

// full step truth table
const boolean fTable[4][4] =
{
  {0, 1, 1, 0},
  {0, 1, 0, 1},
  {1, 0, 0, 1},
  {1, 0, 1, 0}
};

#define CW 1
#define CCW 0

class drive
{
  private:
    uint16_t goalCount, counter; 
    float constFreq, constPeriod, period;
    uint8_t fStep;
    int8_t dir;  
    float motRes, motRpm;
    
  public:
    drive(float freq, float res);
    void setFreq(float freq);
    float debug();
    void routine();
    bool statePin1();
    bool statePin2();
    bool statePin3();
    bool statePin4();
    void setDir(boolean d);
    void setSpd(float rpm);
    float getSpd();
    
};

drive::drive(float freq, float res)
{
  constFreq = freq;
  constPeriod = 1000000.f / constFreq;  // period in microseconds unit
  motRes = abs(res);
}

void drive::setFreq(float freq)
{
  fStep = 0;
  counter = 0;
  period = 1000000.f / freq;   
  goalCount = round(period / constPeriod);
}

float drive::debug()
{
  return goalCount;
}

void drive::routine()
{
  if(counter > goalCount)
  {
    counter = 0;
    fStep++;
    fStep %= 4;
  }
  counter++;  
}

bool drive::statePin1()
{
  return fTable[fStep][abs(0-dir)];
}

bool drive::statePin2()
{
  return fTable[fStep][abs(1-dir)];
}

bool drive::statePin3()
{
  return fTable[fStep][abs(2-dir)];
}

bool drive::statePin4()
{
  return fTable[fStep][abs(3-dir)];
}

void drive::setDir(boolean d)
{
  if(d) dir = 0;
  else  dir = 3; 
}

void drive::setSpd(float rpm)
{
  motRpm = rpm;
  float freg = motRes * motRpm / 60.f;   
  setFreq(freg);
}

float drive::getSpd()
{
  return motRpm;
}



#endif  // DRIVE_H
