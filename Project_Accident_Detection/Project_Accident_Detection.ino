//both LCD and Serial Interface
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h> 
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(2,3); //SIM800L Tx & Rx is connected to Arduino #3 & #2
//i2c pins
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //
#define LED_Pin       13
#define BUZZER_Pin    12
#define LM35          A0
#define Flame_Pin     A1
#define Vibration_Pin A2

float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object  
TinyGPSPlus gps;
int HR_int,MM_int,SS_int,PM,First_Time;
float lat_float,lng_float;
String Date_Str,Time_Str,Location_Str,PM_Str,Message_Str,Message_No;
bool gpsL,gpsD,gpsT;

void setup()
{ 
  //Initialisation
  First_Time=1;
  Serial.begin(9600); // connect serial 
  lcd.clear();
  lcd.begin(16, 2);
  lcd.backlight();//Power on the back light
  pinMode(Flame_Pin, INPUT_PULLUP);
  pinMode(Vibration_Pin, INPUT_PULLUP);
  pinMode(LED_Pin, OUTPUT);
  pinMode(BUZZER_Pin, OUTPUT);
  //Single Run Programs
  Introduction();  //College Name,Project Name,Student Name
  mySerial.begin(9600);
  Send_SMS();
  lcd.clear();
  lcd.print("Test Message Sent");
  delay(2000);
  First_Time=2;
  lcd.clear();
  lcd.print("The GPS Received"); 
  lcd.setCursor(0, 1);
  lcd.print(" Signal:");
  delay(5000);
  delay(5000);
  delay(5000); 
}

void Send_SMS()
{
  if (First_Time==1)
  {
   Message_No= "AT+CMGS=\"+919021702085\""; 
   //Message_No= "AT+CMGS=\"+919820287186\""; 
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);
   lcd.print("Initializing GSM");
   delay(5000);
   delay(5000);
   delay(5000);
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);  
   lcd.print("AT"); //Once the handshake test is successful, it will back to OK
   mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
   delay(1000);
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);   
   lcd.print("AT"); //Once the handshake test is successful, it will back to OK  
   mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
   delay(1000);  
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);   
   lcd.print("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
   mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
   delay(1000);  
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);   
   lcd.print("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
   mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
   delay(1000);
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);   
   lcd.print("AT+CREG?"); //Check whether it has registered in the network
   mySerial.println("AT+CREG?"); //Check whether it has registered in the network
   delay(1000);
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);   
   lcd.print("AT+CMGF=1"); // Configuring TEXT mode
   mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
   delay(1000);
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);   
   lcd.print(Message_No);//change ZZ with country code and xxxxxxxxxxx with phone number to sms
   mySerial.println(Message_No);//change ZZ with country code and xxxxxxxxxxx with phone number to sms
   delay(1000);
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);   
   lcd.print("TEST MESSAGE OK"); //text content   
   mySerial.print("TEST MESSAGE OK"); //text content 
   mySerial.write(26);
   delay(1000);
  }
  else
  {
   //Message_No= "AT+CMGS=\"+919820287186\"";
   //Send_SMS2();
   //Message_No= "AT+CMGS=\"+919029993930\"";
   //Send_SMS2();
   Message_No= "AT+CMGS=\"+919021702085\"";
   Send_SMS2();
   }
}

void Send_SMS2()
{
   lcd.print("AT"); //Once the handshake test is successful, it will back to OK
   mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
   delay(1000);
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);   
   lcd.print("AT"); //Once the handshake test is successful, it will back to OK  
   mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
   delay(1000);  
   lcd.print("AT+CMGF=1"); // Configuring TEXT mode
   mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
   delay(1000);
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);   
   lcd.print(Message_No);//change ZZ with country code and xxxxxxxxxxx with phone number to sms
   mySerial.println(Message_No);//change ZZ with country code and xxxxxxxxxxx with phone number to sms
   delay(1000);
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);  
   lcd.print(Message_Str); //text content   
   mySerial.print(Message_Str); //text content
   mySerial.print(Location_Str); //text content
   mySerial.print(" on "); //text content
   mySerial.print(Date_Str); //text content
   mySerial.print(" at "); //text content
   mySerial.print(Time_Str); //text content
   mySerial.write(26);
   delay(1000);
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
    gpsL=true;
 }
  else
  {
    lcd.clear();
    lcd.print("Location:");
    lcd.setCursor(0 , 1);
    lcd.print(" Not Available");
    delay(2000);
    gpsL=false;
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
    gpsD=true;
    }
  else
  {
    lcd.clear();
    lcd.print("Date:");
    lcd.setCursor(0 , 1);
    lcd.print(" Not Available");
    delay(2000);
    gpsD=false;
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
   gpsT=true;
   }
  else
  {
    lcd.clear();
    lcd.print("Time:");
    lcd.setCursor(0 , 1);
    lcd.print(" Not Available");
    delay(2000);
    gpsT=false;
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

void Sensor_Check()
{
  int Vibration_Val, Flame_Val,Count_Vib;
  float Temp_Val;
  Vibration_Val=digitalRead(Vibration_Pin);
  if (Vibration_Val == 1)
  {
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);
   lcd.print("Accident Detected");
   delay(1000);
   if (gpsL==true && gpsD==true && gpsT==true)
   {
    Message_Str="Accident Alert At Location: "; 
    Send_SMS();
    lcd.clear();
    lcd.print("Send SMS");
    delay(200); 
   }
  }
  
  
  Flame_Val=digitalRead(Flame_Pin);
  if (Flame_Val == 0)
  {
   Message_Str="Fire Alert At Location: "; 
   Send_SMS(); 
   lcd.clear();//Clean the screen
   lcd.setCursor(0, 0);
   lcd.print("Fire Detected  ");
   delay(1000);
  }

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
  delay(500);
}

void loop()
{
  Sensor_Check();
  Get_GPS_Data(); 
   
}
