
#include <Arduino.h>
#ifndef PINCONFIG_H
#define PINCONFIG_H
#include "pinConfig.h"

#define outPinSize 14
const uint8_t outPin[outPinSize] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, A0, A1, A2, A3};

#define INA1 PD4
#define INA2 PD7
#define INB1 PB0
#define INB2 PB4
#define INC1 PC0
#define INC2 PC1
#define IND1 PC2
#define IND2 PC3
#define PWMA OCR2B // pin 3 
#define PWMB OCR1A // pin 9
#define PWMC OCR1B // pin 10
#define PWMD OCR2A // pin 11
#define ENA_AB 5
#define ENA_CD 6

void outPinInit()
{
  for(uint8_t i=0; i<outPinSize; i++)
  {
    pinMode(outPin[i], OUTPUT);
  }

  // reset timer register
  TCCR1A = 0;             
  TCCR1B = 0;              
  TIMSK1 = 0;
  TCCR2A = 0;              
  TCCR2B = 0;
  TIMSK1 = 0;
  TIMSK2 = 0;
                
  // config waveform
  TCCR1A |= (1<<WGM10);
  TCCR1B |= (1<<WGM12); // fast pwm 8 bit
  TCCR2A |= (1<<WGM20);
  TCCR2A |= (1<<WGM21); // fast pwm 
  
  // config prescale
  TCCR1B |= (1<<CS11);  
  TCCR1B |= (1<<CS10);  // prescale 64, 976.5 hz
  TCCR2B |= (1<<CS22);  // prescale 64, 976.5 hz
  
  // config compare match
  TCCR1A |= (1<<COM1A1);  
  TCCR1A |= (1<<COM1B1);  // clear on compare match, set at bottom
  TCCR2A |= (1<<COM2A1);  
  TCCR2A |= (1<<COM2B1);  // clear on compare match, set at bottom

  // enable overflow interrupt
  TIMSK1 |= (1<<TOIE1);  
  TIMSK2 |= (1<<TOIE2);  
 
  // enable interrupt routine
  sei();                      
}

void digitalWrite_A1(boolean state) // port d
{
  state?  PORTD |= (1<<INA1): PORTD &= ~(1<<INA1); 
}

void digitalWrite_A2(boolean state) // port d
{
  state?  PORTD |= (1<<INA2): PORTD &= ~(1<<INA2); 
}

void digitalWrite_B1(boolean state) // port b
{
  state?  PORTB |= (1<<INB1): PORTB &= ~(1<<INB1); 
}

void digitalWrite_B2(boolean state) // port b
{
  state?  PORTB |= (1<<INB2): PORTB &= ~(1<<INB2); 
}

void digitalWrite_C1(boolean state) // port c
{
  state?  PORTC |= (1<<INC1): PORTC &= ~(1<<INC1); 
}

void digitalWrite_C2(boolean state) // port c
{
  state?  PORTC |= (1<<INC2): PORTC &= ~(1<<INC2); 
}

void digitalWrite_D1(boolean state) // port c
{
  state?  PORTC |= (1<<IND1): PORTC &= ~(1<<IND1); 
}

void digitalWrite_D2(boolean state) // port c
{
  state?  PORTC |= (1<<IND2): PORTC &= ~(1<<IND2); 
}

void digitalWrite_AB12(boolean a1, boolean a2, boolean b1, boolean b2)  // mix port a and b
{
  digitalWrite_A1(a1);
  digitalWrite_A2(a2);
  digitalWrite_B1(b1);
  digitalWrite_B2(b2);
}

void digitalWrite_CD12(boolean c1, boolean c2, boolean d1, boolean d2)  // mix port c and d
{
  digitalWrite_C1(c1);
  digitalWrite_C2(c2);
  digitalWrite_D1(d1);
  digitalWrite_D2(d2);
}

void setPWM_A(uint8_t pwm)
{
  PWMA = pwm;
}

void setPWM_B(uint8_t pwm)
{
  PWMB = pwm;
}

void setPWM_C(uint8_t pwm)
{
  PWMC = pwm;
}

void setPWM_D(uint8_t pwm)
{
  PWMD = pwm;
}

void setPWM_AB(uint8_t pwm) // mix pwm a and b
{
  setPWM_A(pwm);
  setPWM_B(pwm);
}

void setPWM_CD(uint8_t pwm) // mix pwm c and d
{
  setPWM_C(pwm);
  setPWM_D(pwm);
}

void enable_AB(boolean state)
{
  digitalWrite(ENA_AB, state);
}

void enable_CD(boolean state)
{
  digitalWrite(ENA_CD, state);
}


#endif  // PINCONFIG_H
