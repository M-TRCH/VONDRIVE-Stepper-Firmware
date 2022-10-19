
#include "pinConfig.h"
#include "Drive.h"

// drive classname(interrupt freq, motor res)
drive step1(976.5, 200);
drive step2(976.5, 200);

ISR(TIMER1_OVF_vect)  
{   
  step1.routine();
  digitalWrite_AB12
  (
    step1.statePin1(),
    step1.statePin2(),
    step1.statePin3(),
    step1.statePin4()
  );
}

ISR(TIMER2_OVF_vect)  
{ 
  step2.routine();
  digitalWrite_CD12
  (
    step2.statePin1(),
    step2.statePin2(),
    step2.statePin3(),
    step2.statePin4()
  );
}

void drive1(int spd, int duty)
{
  duty = constrain(duty, 0, 255);
  if(spd == 0 || duty == 0) 
  {
    enable_AB(false);  
  }
  else
  {
    enable_AB(true);
    setPWM_AB(duty);
    if(spd > 0)
    {
      step1.setDir(CCW);      
      step1.setSpd(spd);
    }
    else
    {
      step1.setDir(CW);
      step1.setSpd(abs(spd));   
    }
  }  
}

void drive2(int spd, int duty)
{
  duty = constrain(duty, 0, 255);
  if(spd == 0 || duty == 0) 
  {
    enable_CD(false);  
  }
  else
  {
    enable_CD(true);
    setPWM_CD(duty);
    if(spd > 0)
    {
      step2.setDir(CCW);      
      step2.setSpd(spd);
    }
    else
    {
      step2.setDir(CW);
      step2.setSpd(abs(spd));   
    }
  }  
}

void setup() 
{
  Serial.begin(115200);
  Serial.setTimeout(100);
  
  // output initialize
  outPinInit();
  
}

// serial commu
#define bufSize 5 
int dataBuf[bufSize];

void serialEvent() 
{
  if(Serial.find('#'))
  {
    for(int i=0; i<bufSize; i++)
    {
      dataBuf[i] = Serial.parseInt();         
    }
    drive1(dataBuf[0], dataBuf[1]);
    drive2(dataBuf[2], dataBuf[3]);
    Serial.flush();
  }
}

void loop() 
{  
  
}
