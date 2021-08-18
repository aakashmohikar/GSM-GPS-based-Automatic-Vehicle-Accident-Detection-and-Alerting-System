#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> 
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(2,3); //SIM800L Tx & Rx is connected to Arduino #3 & #2
//i2c pins
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

int First_Time;

void setup()
{
  First_Time=1;
  //WE define our LCD 16 columns and 2 rows
  lcd.begin(16,2);
  lcd.backlight();//Power on the back light
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
  Introduction();  //College Name,Project Name,Student Name
  Send_SMS(); 
  First_Time=2;
}

void loop()
{
  
}

void Send_SMS()
{
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("Initializing GSM");
  delay(1000);
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
  lcd.print("AT+CMGS=\"+919021702085\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  mySerial.println("AT+CMGS=\"+919021702085\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(1000);
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);   
  if (First_Time==1)
  {
   lcd.print("TEST MESSAGE OK"); //text content   
   mySerial.print("TEST MESSAGE OK"); //text content 
  }
  else
  {
   lcd.print("ACCIDENT AT LOCATION :"); //text content   
   mySerial.print("ACCIDENT AT LOCATION :"); //text content
  }
  mySerial.write(26);
  delay(1000);
}
void Introduction()
{
  //College Name
  lcd.setCursor(0, 0); //we start writing from the first row first column
  lcd.print("THAKUR COLLEGE"); 
  lcd.setCursor(0, 1);//we start writing from the second row first column
  lcd.print("OF ENGG. & TECH");
  delay(3000);
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
  lcd.print("HARISH PATEL    ");
  delay(2000);
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
