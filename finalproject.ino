
//#include <LiquidCrystal.h>

#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h> // including servo library.

#define FIREBASE_HOST "physiobot-45ff3-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "u2jG6XxCGbVdmR7aXVQ26OLtcgDmvNXixmNvqIQm"
#define button_pin 2 //connect switch to D4
char ssid[] = "Diti";
char pass[] = "aaditi2001";

WiFiServer server(80);
//const int rs=12,en=11,d4=5,d5=4,d6=3,d7=2;
//LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
Servo servo_1; // Giving name to servo.
int pos;
int potpin;
int val;
int c;
int k=0;
int  t1,t2=0;
int z;
int angle;

/*int readpot(int potpin)
{
  val = analogRead(potpin); // connect potpin to A0
  angle=map(val,0,1023,0,180);
  return angle;
  }
*/
void setup (){
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  servo_1.attach(button_pin); //connect servo to D4 pin
  //pinMode(button_pin,INPUT_PULLUP);
  /*lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);*/
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  delay(2000);
}


void loop(){
  //Serial.println("Enter angle:");
  //while(Serial.available()==0){}
  //angle=Serial.parseInt();
  val=analogRead(potpin);
  int angle=map(val,0,1023,0,90);

  if (angle>0) {
  
  //if(digitalRead(button_pin)==1)
  //{
  for (pos = 0; pos <= angle; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
    
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);  // waits 15ms for the servo to reach the position
  }
    delay(1000);
  for (pos = angle; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); // waits 15ms for the servo to reach the position
  }
   delay(1000);
     k++;
     c=k;
   if (t1==0)
   {
    t1=millis();
   }
   else
   {
    t2=millis()-t1;
   }
   z=t2;
   Firebase.setInt("Physiobot2O/patient status/angle",angle);
   if(Firebase.failed())
  {
    Serial.print("Setting log failed");
    Serial.println(Firebase.error());
  }
  //}
  //if(digitalRead(button_pin)==0)
  //{
  }
  if(angle==0){
   if (z<60000) 
    {
     Serial.print(z/1000);
     Serial.println("sec");
  Firebase.setFloat("Physiobot2O/patient status/Time",z/1000);
    }
    else if (z>=60000)
    {
      Serial.print(z/60000);
      Serial.println("min");
  Firebase.setFloat("Physiobot2O/patient status/Time",z/60000);
    }
  
  Serial.println(c);
  Firebase.setInt("Physiobot2O/patient status/Count",c);
  if(Firebase.failed())
  {
    Serial.print("Setting log failed");
    Serial.println(Firebase.error());
  }
  k=0;
  t1=0;
  }
  /*lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Angle:");
  lcd.setCursor(6,0);
  lcd.print(angle);
  lcd.setCursor(0,1);
  lcd.print("Count:");
  lcd.setCursor(6,1);
  lcd.print(c);*/
}
