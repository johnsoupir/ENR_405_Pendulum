extern volatile long counter;
#define encoderA 2
#define encoderB 3

//Sub-process allowing the encoder values to be counted rather than measured each itteration
void encoderA_Handler() 
{ 
  if(digitalRead(encoderB)==LOW)
  {
    counter ++;
  }
  else
  {
    counter --; 
  }
}

void encoderB_Handler() 
{
  if(digitalRead(encoderA)==LOW)
  {
    counter--; 
  }
  else
  {
    counter++;
  }
}

void initEncoder()
{
  //pinMode(encoderA, INPUT_PULLUP);
  //pinMode(encoderB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderA), encoderA_Handler, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderB), encoderB_Handler, RISING);
}
