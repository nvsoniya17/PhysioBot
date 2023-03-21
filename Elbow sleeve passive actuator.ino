#include <ArduinoJson.h>
#include <FirebaseArduino.h>

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define FIREBASE_HOST "physiobot-45ff3-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "u2jG6XxCGbVdmR7aXVQ26OLtcgDmvNXixmNvqIQm"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "JTwdpqNOvJzhAQKWL9mnjzHUiqtM5D1b";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SONIYA";
 char pass[] = "9443054736";
#include <Servo.h> // including servo library.

Servo servo_1; // Giving name to servo.
int pos=0;
int maxpos=0;
int dly=0;
int swt=0;
int c;
int k=0;
int  t1,t2=0;
int z;

BLYNK_WRITE(V1)
{
  swt=param.asInt();
}
BLYNK_WRITE(V2)
{
  dly=param.asInt();
}
BLYNK_WRITE(V3)
{
  maxpos=param.asInt();
}

void setup (){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  servo_1.attach(0); // Attaching Servo to D3
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}


void loop(){
  Blynk.run();
  if(swt)
  {
    //Firebase.setInt("Angle",maxpos);
  for (pos = 0; pos <= maxpos; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
    
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(dly);                       // waits 15ms for the servo to reach the position
  }
    delay(1000);
  for (pos = maxpos; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(dly);                       // waits 15ms for the servo to reach the position
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
  }
  if(!swt)
  {
    if (z<60000) 
    {
     Serial.println(z/1000);
  Blynk.virtualWrite(V5,z/1000," ","sec");
  //Firebase.setFloat("Time",z/1000);
    }
    else if (z>=60000)
    {
      Serial.println(z/60000);
  Blynk.virtualWrite(V5,z/60000," ","min");
  Firebase.setFloat("Time",z/60000);
    }
  
  Serial.println(c);
  Blynk.virtualWrite(V4,c);
  Firebase.setInt("Count",c);
  k=0;
  t1=0;
  }
}
