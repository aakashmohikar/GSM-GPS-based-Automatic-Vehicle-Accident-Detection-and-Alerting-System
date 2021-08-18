
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //

#define LM35          A0   //LM35 Module Analog out pin connected to A0 pin of Arduino

void setup()
{ 
  //Initialisation
  lcd.begin(16, 2);
  lcd.clear();
  lcd.backlight();//Power on the back light
}

void loop()
{
  float Temp_Val;
  
  Temp_Val = analogRead(LM35);                                                   
  Temp_Val = (Temp_Val * 71.22) /(1024);
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("TEMP.= ");
  lcd.print(Temp_Val,2);
  lcd.print(" \xDF");
  lcd.println("C   ");
  if (Temp_Val>50.00)
  {
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);
   lcd.print("High Temperature");
   lcd.setCursor(0, 1);
   lcd.print("  Detected      "); 
  }
  delay(1000);
}
