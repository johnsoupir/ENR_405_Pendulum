#define pwmL 6
#define pwmR 9
#define enR 7
#define enL 8

/* Motor Data */
// No load motor current -> 105mA
// Stall motor current -> 1.5 A

void initMotor()
{
  pinMode(pwmL,OUTPUT);
  pinMode(pwmR,OUTPUT);
  pinMode(enR,OUTPUT);
  pinMode(enL,OUTPUT);
  digitalWrite(enR,HIGH);
  digitalWrite(enL,HIGH);
}

void testMotor()
{
  digitalWrite(pwmL,HIGH);
  delay(100);
  digitalWrite(pwmL,LOW);
}

void setMotor(int velocity)
{
  //Serial.print("MOTOR --> ");
  //Serial.println(velocity);
  //Forward move
  if(velocity > 0)
  {
    analogWrite(pwmL,0);
    analogWrite(pwmR,abs(velocity));
  }
  else 
  //Reverse move
  if (velocity < 0)
  {
    analogWrite(pwmR,0);
    analogWrite(pwmL,abs(velocity));
  }
  //Stop
  else
  {
    analogWrite(pwmR,0);
    analogWrite(pwmL,0);
  }
}




void voltMotor(float volts)
{

  
  int velocity = volts*10.625;
  //Serial.print("MOTOR --> ");
  //Serial.println(velocity);
  //Forward move
  if(velocity > 0)
  {
    analogWrite(pwmL,0);
    analogWrite(pwmR,abs(velocity));
  }
  else 
  //Reverse move
  if (velocity < 0)
  {
    analogWrite(pwmR,0);
    analogWrite(pwmL,abs(velocity));
  }
  //Stop
  else
  {
    analogWrite(pwmR,0);
    analogWrite(pwmL,0);
  }
}
