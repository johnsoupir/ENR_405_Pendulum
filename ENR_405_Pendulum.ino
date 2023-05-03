#include "motor.h"
#include "encoder.h"
#include "endStops.h"
#include "display.h"
#include "buttons.h"

volatile long temp, counter = 600;  //Counts encoder tics
float output;                       //Output of PID function
float dir;                          //Direction of pendulum. 1=up || -1=down


/* PID VALUES.*/
float Kt = 1; //Theta gain. Used to scale error.
float Kp;
float Ki; 
float Kd; 


/* Very decent working
void upwardPID()
{
  //Kp = 135;
  Kp = 140;
  Ki = 1.25;
  Kd = 2000;
  dir = 1;
}
*/

/* Sets PID values to upward values */
void upwardPID()
{
  //Kp = 135;
  Kp = 145; // 135;
  Ki = 1.215; // 1.23;
  Kd = 3050; //00;
  dir = 1;
}

/* Sets PID values to downward values */
void downwardPID()
{
  Kp = 100;
  Ki = 0.1; // 0.2;//0.5; // 0.01;
  Kd = 0;// 500;// 280; // 120;
  dir = -1;
}

//PID Function uses these 
float T, oldT = 0;       //Time and last time
float dT = 0;            //Time delta
float olddT = 0;         //Late time delta
float err, olderr = 0;   //Error and last error

float I, oldI = 0;       //I and last I value
float P, oldP = 0;       //P and last P value
float D, oldD = 0;       //D and last D value

//PID of maximum angle in ticks we will try to recover from. If it goes past here we give up.
float maxAngle = 100;

//Time to delay each loop in ms 
int sleepTime = 2; 

//Limit motor voltage for safety
int motorLimit=12;








void setup() { 
  Serial.begin(921600);                       //Start serial connection at 115200 baud rate
  delay(500);                                 //Wait half a second for serial to begin
  Serial.println("LOG --> Init Controller!"); //Say hello
  initEncoder();                              //Set up encoder pins and attach interrupt handlers
  initButtons();                              //Set up button pins
  initLCD();                                  //Set up and init the I2C LCD
  initMotor();                                //Set up motor pins
  initEndstops();
  autoHome();
  menu();
}

void loop(){        
  if(stopButton() || abs(counter) > 100 || trippedEndstops()) 
  {
    setMotor(0);
    menu();
  }
  //If the rod is at the center stop the motor
  if (counter == 0)
  {
    setMotor(0);
    Serial.println("LOG -> STABLE");
  }
  output = PID((float)(counter*0.005236)); //Input error in radians into PID function which returns PID output as motor voltage
  output=constrain(output,-motorLimit,motorLimit); //Constrain output to be within the max motor limit
  voltMotor((int)-output);
  Serial.print((String)millis() + " ");
  Serial.println(counter);  
  lcd.setCursor(4,0);
  lcd.print(String((float)output));  
}

//PID function. Takes radians as input, returns motor voltage.
float PID(float err)
{
  T = (float)millis();                                   //Get current time since boot in ms 
  dT =  (float)(T - oldT);                               //Get delta T (T - last T)
  float c_err = err ;//* Kt;                             //This is corrected error. Equal to Kt*error. This is to scale error if needed.
  P = c_err * Kp;                                        //Proportional part. Equal to error * proportional gain.
  I = ( oldI + (c_err * dT )) * Ki;                      //Integral part. Equal to (last I + (error * integral gain)) * integral gain.
  D = ((float)(c_err-olderr)/(float)dT) * (float)Kd;     //Derivative part. Equal to ((error - last error)/delta T) * Derivative gain.

  oldT = T;                                              //Calcs are done. Now we store current T as last T.
  olderr = err;                                          //Same for error. Store current error as last error.
  oldI += ((c_err*dT)*Ki);                               //Update last I.
  return dir*(P+I+D);                                    //Return the sum of P I D. Multiply by dir, which is 1 or -1 to set the direction.
}


//Menu function allows mode selection on LCD and zeros the encoder.
void menu()
{
  oldI=0;
  olderr=0;
  clearLCD();                     //Clears LCD display
  lcd.setCursor(0,0);             //Set cursor to char 0, line 0
  lcd.print("Pick mode");         //Print text
  lcd.setCursor(6,1);
  lcd.print("STOP");
  while(!goButton())              //Wait for go button to be pressed, and keep checking direction switch. 
  {
    if(dirButton())               //If the direction is up, set to up.
    {
      lcd_upwardMode();
      upwardPID();
      counter=601;
    }
    else                          //Otherwise we set ddown mode.
    {
      lcd_downwardMode();
      downwardPID();
      counter=0;
    }
    delay(1);                     //Delay to keep the LCD from refreshing too fast.
  }
  lcd.setCursor(0,1);             
  lcd.print("GO        ");
  lcd.setCursor(0,0);
  if(dir==1)
  {
  lcd.print("Lift rod CCW");
  Serial.println("GO!");
  }
  while(counter!=0);
  lcd.setCursor(0,0);
  lcd.print("PID:        ");
  lcd.setCursor(4,0);
  lcd.print("      ");
}


void autoHome()
{
    
  setMotor(30);
  while(!trippedEndstops());
  Serial.println("Hit left endstop.");
  setMotor(0);
  Serial.println("Stop motor.");
  int time1 = millis();
  setMotor(-30);
  Serial.println("Going other way.");
  delay(500);
  while(!trippedEndstops());
  int crossingTime = millis() - time1;
  int homeTime=crossingTime/2;
  int beginMoveTime = millis();
  setMotor(30);
  delay(500);
  while(  (millis() < beginMoveTime+homeTime) && !trippedEndstops());
  setMotor(0);
}