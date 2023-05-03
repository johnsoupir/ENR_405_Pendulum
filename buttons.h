#define GO    10
#define STOP  11
#define DIR   12

void initButtons()
{
  pinMode(GO,INPUT_PULLUP);
  pinMode(STOP,INPUT_PULLUP);
  pinMode(DIR,INPUT_PULLUP);
}

bool goButton()
{
  return !(bool)digitalRead(GO);
}

bool stopButton()
{
  return !(bool)digitalRead(STOP);
}

bool dirButton()
{
  return !(bool)digitalRead(DIR);
}
