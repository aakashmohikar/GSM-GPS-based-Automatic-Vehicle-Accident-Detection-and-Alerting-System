/*-----( Import library )-----*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//i2c pins
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // 

void setup() 
{
//WE define our LCD 16 columns and 2 rows
lcd.begin(16,2);
lcd.backlight();//Power on the back light
//lcd.backlight(); Power off the back light
}


void loop() 
{
  //College Name
  lcd.setCursor(0, 0); //we start writing from the first row first column
  lcd.print("THAKUR COLLEGE"); 
  lcd.setCursor(0, 1);//we start writing from the second row first column
  lcd.print("OF ENGG. & TECH");
  delay(2000);
  //Project Name
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("GSM & GPS BASED "); 
  lcd.setCursor(0, 1);
  lcd.print("AUTOMATIC VEHICLE");
  delay(2000);
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0); 
  lcd.print("ACCIDENT DETECTN"); 
  lcd.setCursor(0, 1);
  lcd.print("& ALERTING SYS.  ");
  delay(2000);
  //STUDENT NAME
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("   PROJECT BY   ");
  lcd.setCursor(0, 1);
  lcd.print("AAKASH MOHIKAR  ");
  delay(2000);
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("AJAYKUMAR MAURYA");
  lcd.setCursor(0, 1);
  lcd.print("HARSH PATEL    ");
  delay(2000);
}
