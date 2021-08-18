//both LCD and Serial Interface
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //

#define Vibration_Pin  A2  //Vibration module output connected to A2 pin of Arduino

void setup()
{ 
  //Initialisation
  lcd.begin(16, 2);
  lcd.clear();
  lcd.backlight();//Power on the back light
  pinMode(Vibration_Pin, INPUT_PULLUP);
}


void loop()
{
  int Vibration_Val ;
  
  Vibration_Val=digitalRead(Vibration_Pin);
  if (Vibration_Val == 1)
  {
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);
   lcd.print("Accident Detected");
   delay(1000);
   }
 
   delay(1000);
}
