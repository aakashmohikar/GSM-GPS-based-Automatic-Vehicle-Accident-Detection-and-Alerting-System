//both LCD and Serial Interface
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
//i2c pins
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //
#define LED_Pin       13
#define BUZZER_Pin    12
#define LM35          A0
#define Flame_Pin     A1
#define Vibration_Pin A2

float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object  
TinyGPSPlus gps;
int HR_int,MM_int,SS_int,PM;
float lat_float,lng_float;
String Date_Str,Time_Str,Location_Str,PM_Str;

void setup()
{ 
  //Initialisation
  Serial.begin(9600); // connect serial 
  lcd.clear();
  lcd.print("The GPS Received Signal:"); 
  lcd.begin(16, 2);
  lcd.backlight();//Power on the back light
  pinMode(Flame_Pin, INPUT_PULLUP);
  pinMode(Vibration_Pin, INPUT_PULLUP);
  pinMode(LED_Pin, OUTPUT);
  pinMode(BUZZER_Pin, OUTPUT);
  //Single Run Programs
  Introduction();  //College Name,Project Name,Student Name

}

void displayInfo()
{ 
  if (gps.location.isValid())
  {
    lcd.clear();
    lcd.setCursor(0 , 0);
    lcd.print("Lat= ");
    lcd.print(gps.location.lat(), 6);
    lcd.setCursor(0 , 1);
    lcd.print("Lng= ");
    lcd.print(gps.location.lng(), 6);
    lat_float=gps.location.lat();
    lng_float=gps.location.lng();
    delay(2000);
    Location_Str=String(gps.location.lat(), 6) + " " + String(gps.location.lng(), 6);
    lcd.clear();
    lcd.print(Location_Str);
    delay(2000);
 }
  else
  {
    lcd.print("Location: Not Available");
  }
  
  if (gps.date.isValid())
  {
    lcd.clear();
    lcd.setCursor(0 , 0);
    lcd.print("Date= ");
    lcd.print(gps.date.day());
    lcd.print("/");
    lcd.print(gps.date.month());
    lcd.print("/");
    lcd.print(gps.date.year());
    Date_Str=String(gps.date.day()) + "/" + String(gps.date.month()) + "/" + String(gps.date.year()) ;
    lcd.clear();
    lcd.print(Date_Str);
    delay(2000);
  }
  else
  {
    lcd.print("Not Available");
  }

  if (gps.time.isValid())
  {
    HR_int=gps.time.hour()+ 5;
    MM_int=gps.time.minute()+30;
    SS_int=gps.time.second();
    if (MM_int > 59 )
    {
      HR_int=HR_int + 1;
      MM_int=MM_int - 59;
    }
    if (HR_int > 12 )
    {
      HR_int=HR_int - 12;
      PM=1;
    }
    else
    {
      PM=0;
    }
    lcd.setCursor(0 , 1);
    lcd.print("Time=");
    if (HR_int <10)
    {
     lcd.print("0");   
     lcd.print(HR_int);   
    }
    else
    {
    lcd.print(HR_int);  
    }
    
    lcd.print(":");
    if (MM_int <10)
    {
     lcd.print("0");   
     lcd.print(MM_int);   
    }
    else
    {
    lcd.print(MM_int);  
    }
    lcd.print(":");
    if (SS_int <10)
    {
     lcd.print("0");   
     lcd.print(SS_int);   
    }
    else
    {
    lcd.print(SS_int);  
    }    
    if (PM==1)
    {
      lcd.print(" PM");
      PM_Str="PM";
    }
    else
    {
      lcd.print(" AM");
      PM_Str="AM";
    }
   Time_Str=String(HR_int) + ":" + String(MM_int) + " " + PM_Str ;
   lcd.clear();
   lcd.print(Time_Str);
   delay(2000); 
  }
  else
  {
    lcd.print("Not Available");
  }
  delay(1000);
}

void Introduction()
{
  //College Name
  lcd.setCursor(0, 0); //we start writing from the first row first column
  lcd.print("THAKUR COLLEGE"); 
  lcd.setCursor(0, 1);//we start writing from the second row first column
  lcd.print("OF ENGG. & TECH");
  delay(500);
  //Project Name
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("GSM & GPS BASED "); 
  lcd.setCursor(0, 1);
  lcd.print("AUTOMATIC VEHICLE");
  delay(500);
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0); 
  lcd.print("ACCIDENT DETECTN"); 
  lcd.setCursor(0, 1);
  lcd.print("& ALERTING SYS.  ");
  delay(500);
  //STUDENT NAME
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("   PROJECT BY   ");
  lcd.setCursor(0, 1);
  lcd.print("AAKASH MOHIKAR  ");
  delay(500);
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("AJAYKUMAR MAURYA");
  lcd.setCursor(0, 1);
  lcd.print("HARISH PATEL    ");
  delay(500);
}

void Debug_GPS()
{
  // Displays information when new sentence is available.
  while (Serial.available() > 0)
    lcd.print(Serial.read());
 }

void Get_GPS_Data()
{
   while (Serial.available() > 0)
    if (gps.encode(Serial.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    lcd.print(F("No GPS detected"));
    while(true);
  }
}

void loop()
{
 Get_GPS_Data();
}
