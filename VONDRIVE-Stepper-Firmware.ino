
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

void setup() 
{
  Serial.begin(115200);

  // output initialize
  outPinInit();

  // motor 1 
  enable_AB(true);  
  setPWM_AB(50);
  step1.setDir(CCW);
  step1.setSpd(50.f);

  // motor 2 
  enable_CD(true);  
  setPWM_CD(100);
  step2.setDir(CW);
  step2.setSpd(250.f);
 
}

void loop() 
{  
  delay(1000);
}
