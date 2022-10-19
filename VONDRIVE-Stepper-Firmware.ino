
#include "pinConfig.h"
#include "Drive.h"
#include "Analog.h"

// drive classname(interrupt freq, motor res)
drive step1(976.5, 200);
drive step2(976.5, 200);

// current control
struct pid
{
  float Kp;
  float Ki;
  float Kd;
  volatile float sp, pv, error, p, i, d, cps;
} pid1, pid2;

#define av 51.f
#define rSen 0.01f

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

  // current control
  pid1.pv = ((getADC4_samp() / 1024.f * 5.f) / av) / rSen;
  pid1.error = pid1.sp - pid1.pv;
  pid1.p = pid1.Kp * pid1.error;
  pid1.cps = pid1.p + pid1.i + pid1.d;
  pid1.cps = constrain(pid1.cps, 0, 255);
  setPWM_AB(pid1.cps);
 
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

  // current control
  pid2.pv = ((getADC5_samp() / 1024.f * 5.f) / av) / rSen;
  pid2.error = pid2.sp - pid2.pv;
  pid2.p = pid2.Kp * pid2.error;
  pid2.cps = pid2.p + pid2.i + pid2.d;
  pid2.cps = constrain(pid2.cps, 0, 255);
  setPWM_CD(pid2.cps);
  
}

ISR(ADC_vect)
{
  // read mode
  if(analogFlag)
  {
    // get analog value
    analogVal[muxCount] = ADCL | (ADCH<<8);

    // adc4 event 
    if(muxCount == 0)
    {
      analogSum[muxCount] += analogVal[muxCount];
      ADC4_countSamp++;
    }
    // adc5 event 
    else if(muxCount == 1)
    {
      analogSum[muxCount] += analogVal[muxCount];
      ADC5_countSamp++;
    }
        
    // change pin
    muxCount++;
    muxCount %= analogPinSize;
    selectMux(muxCount);

  }
  // switch mode
  analogFlag++;
  analogFlag %= 2;

}

void setup() 
{
  Serial.begin(115200);

  // output initialize
  outPinInit();

  // analog to digital init
  adcInit();
  
  // motor 1 
  enable_AB(true);  
  setPWM_AB(100);
  step1.setDir(CCW);
  step1.setSpd(50.f);
  
  // motor 2 
  enable_CD(true);  
  setPWM_CD(100);
  step2.setDir(CW);
  step2.setSpd(50.f);

  // config pid gain
  pid1.Kp = 400.f;
  pid1.Ki = 0.f;
  pid1.Kd = 0.f;
  pid2.Kp = 400.f;
  pid2.Ki = 0.f;
  pid2.Kd = 0.f;

  // config setpoint
  pid1.sp = 0.7f;
  pid2.sp = 0.7f;

}

void loop() 
{  
  delay(1000);
}
