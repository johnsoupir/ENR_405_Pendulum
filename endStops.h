#define endstopL 8
#define endstopR 7


void initEndstops()
{
  pinMode(endstopL, INPUT_PULLUP);
  pinMode(endstopR, INPUT_PULLUP);
}

bool trippedEndstops()
{
  //Serial.print("Endstop L: ");
  //Serial.println(digitalRead(endstopL));
  //Serial.print("Endstop R: ");
  //Serial.println(digitalRead(endstopR));
  if( digitalRead(endstopL) != digitalRead(endstopR) )
  {
    return true;
  }
  else
  {
    return false;
  }
}
