
#include <Arduino.h>
#ifndef ANALOG_H
#define ANALOG_H
#include "Analog.h"

#define analogPinSize 4
volatile int analogVal[analogPinSize], analogSum[analogPinSize];
volatile int ADC4_countSamp, ADC5_countSamp;
volatile int muxCount, analogFlag;

void adcInit()
{
  // reset adc register
  ADMUX = 0;
  ADCSRA = 0;
  ADCSRB = 0;
  ADCL = 0;
  ADCH = 0;
  DIDR0 = 0;

  // config volt ref
  ADMUX |= (1<<REFS0);

  // init mux = ADC4
  ADMUX |= (1<<MUX2);
    
  // set adc enable, start, triger and interrupt
  ADCSRA |= (1<<ADEN);  
  ADCSRA |= (1<<ADSC);
  ADCSRA |= (1<<ADATE);
  ADCSRA |= (1<<ADIE);

  // disable output pin
  DIDR0 |= (1<<ADC0D);
  DIDR0 |= (1<<ADC1D);
  DIDR0 |= (1<<ADC2D);
  DIDR0 |= (1<<ADC3D);

  ADC4_countSamp = 0;
  ADC5_countSamp = 0;
  muxCount = 0;
  analogFlag = 0;
}

void selectMux(int state)
{
  // reset mux
  ADMUX &= B11110000;
  
  switch(state)
  {
    case 0: // set adc4
      ADMUX |= (1<<MUX2);
      break;
    case 1: // set adc5
      ADMUX |= (1<<MUX0);
      ADMUX |= (1<<MUX2);
      break;
    case 2: // set adc6
      ADMUX |= (1<<MUX1);
      ADMUX |= (1<<MUX2);
      break;
    case 3: // set adc7
      ADMUX |= (1<<MUX0);
      ADMUX |= (1<<MUX1);
      ADMUX |= (1<<MUX2);
      break;
  }
}

int getADC4_samp()
{
  int samp = analogSum[0] / ADC4_countSamp;
  analogSum[0] = 0;
  ADC4_countSamp = 0;
  return samp;
}

int getADC5_samp()
{
  int samp = analogSum[1] / ADC5_countSamp;
  analogSum[1] = 0;
  ADC5_countSamp = 0;
  return samp;  
}

int getADC6_samp()
{
  return analogSum[2];
}

int getADC7_samp()
{
  return analogSum[3];
}

#endif // ANALOG_H
