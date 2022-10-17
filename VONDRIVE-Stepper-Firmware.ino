
volatile unsigned long prevTime, currTime;
volatile float diffTime;

// full step truth table
const boolean table[4][4] =
{
  {0, 1, 1, 0},
  {0, 1, 0, 1},
  {1, 0, 0, 1},
  {1, 0, 1, 0}
};

// stepper motor drive
#define normalPeriod 2040.f
// in microseconds unit
// or 490.2 hz

uint16_t multip1, multip2;  
uint16_t counter1, counter2;  
float period1, period2;

uint8_t step1, step2;  

#define pinA1 4
#define pinA2 7
#define pinB1 8
#define pinB2 12

// isr at 490 hz
ISR(TIMER1_OVF_vect)  
{ 
  if(counter1 > multip1)
  {
    counter1 = 0;
//    currTime = micros();
//    diffTime = currTime - prevTime;
//    prevTime = currTime;

    step1++;
    step1 %= 4;
    
    digitalWrite(pinA1, table[step1][0]);
    digitalWrite(pinA2, table[step1][1]);
    digitalWrite(pinB1, table[step1][2]);
    digitalWrite(pinB2, table[step1][3]);
  }
  counter1++;
}

ISR(TIMER2_OVF_vect)  
{ 
  
}

void timerInit()
{
  TIMSK1 = 1<<TOIE1;  // enable timer ovf interrupt
  TIMSK2 = 1<<TOIE2;  //  
}

void setFreq1(float freq)
{
  step1 = 0;
  counter1 = 0;
  period1 = 1000000.f / freq;   
  multip1 = round(period1 / normalPeriod);
}

void setup() 
{
  Serial.begin(115200);

  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);
  
  #define constPwm 100
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  analogWrite(3, constPwm);
  analogWrite(9, constPwm);
  
  timerInit();
  setFreq1(220);
 
}

void loop() 
{  
  Serial.println(analogRead(A4));
}
