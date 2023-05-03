#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



byte upArrow[] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00000,
  B00000
};

byte downArrow[] = {
  B00000,
  B00000,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100
};

LiquidCrystal_I2C lcd(0x27,20,2);


void initLCD(){
  

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Auto homing cart!");
  lcd.createChar(0,upArrow);
  lcd.createChar(1,downArrow);

}


void clearLCD()
{
  lcd.clear();
}


void lcd_upwardMode()
{

  lcd.setCursor(13,0);
  lcd.print("DIR: ");
  lcd.setCursor(14,1);
  lcd.write(0);
}



void lcd_downwardMode()
{

  //lcd.clear();
  lcd.setCursor(13,0);
  lcd.print("DIR: ");
  lcd.setCursor(14,1);
  lcd.write(1);
}

void lcdGo()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GO!");
}

void lcdStop()
{
  
}


