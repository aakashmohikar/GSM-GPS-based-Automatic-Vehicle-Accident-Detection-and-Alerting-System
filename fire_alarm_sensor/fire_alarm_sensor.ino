//both LCD and Serial Interface
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //

#define Flame_Pin     A1


void setup()
{ 
  //Initialisation
  lcd.begin(16, 2);
  lcd.clear();
  lcd.backlight();//Power on the back light
  pinMode(Flame_Pin, INPUT_PULLUP);
}


void loop()
{
  int  Flame_Val;
   
  Flame_Val=digitalRead(Flame_Pin);
  if (Flame_Val == 0)
  {
   
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);
   lcd.print("Fire Detected  ");
   delay(1000);
  }
  delay(1000);
}
