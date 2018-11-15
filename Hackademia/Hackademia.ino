#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
//#include <Wire.h>
//#include "RTClib.h"
//RTC_DS1307 RTC;

#define WIFI_SSID "hello" //comlabwifi-hihi
#define WIFI_PASSWORD "walakokabalo" //uhackademia

#define FIREBASE_HOST "u-hackademia-davao-durian.firebaseio.com"
#define FIREBASE_AUTH "WA8WBf4aGE80jG2smPsHFOWHrt0x9dOaYV7arp61"

#define res D6
#define ledPower D5
#define relaywaterlevellowPUMP D4
#define relaywaterlevelhighPUMP D3
#define sensor A0
int sensorValue = 0;
int waterlevelLOW = 1;
int waterlevelNORMAL = 2;
int waterlevelHIGH = 3;
int switch2 =0;



void setup() {
  Serial.begin(115200);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  delay(1000);
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(2000);
  }

  else {
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());
  delay(2000);
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(res, OUTPUT);
  pinMode(ledPower, OUTPUT);
  pinMode(relaywaterlevellowPUMP, OUTPUT);
  pinMode(relaywaterlevelhighPUMP, OUTPUT);
  pinMode(sensor,INPUT);
  digitalWrite(res, HIGH);

}
void loop() {
//  rtc();
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int switch1 = Firebase.getInt("arduinoDevice/Switch");
  Serial.println(switch1);
   if (switch1 == 1){  
   readSensor();
   doAction();
   }

   else
   {
    digitalWrite(relaywaterlevellowPUMP, HIGH);
    digitalWrite(relaywaterlevelhighPUMP, HIGH);
    readSensor();
   }
   
   if (Firebase.failed())
      {
      Serial.println("setting number failed:");
      Serial.println(Firebase.error());
      firebaseReconnect();
      //return;
      }

}

void readSensor() {
  sensorValue = analogRead(sensor);
 if (sensorValue<50){
     Firebase.set("arduinoDevice/waterLevel" ,waterlevelLOW);
//     Firebase.set("arduinoDevice/Time" ,now.year());
     
    }
    else if(sensorValue>=50 && sensorValue<=100){
      Firebase.set("arduinoDevice/waterLevel" ,waterlevelNORMAL);
    }
    else if(sensorValue>=100){
     Firebase.set("arduinoDevice/waterLevel" ,waterlevelHIGH);
    }
}

void doAction(){
 
  if (sensorValue<50){
    digitalWrite(relaywaterlevellowPUMP, LOW);
    digitalWrite(relaywaterlevelhighPUMP, HIGH);
    }
    else if(sensorValue>=50 && sensorValue<100){
      digitalWrite(relaywaterlevellowPUMP, HIGH);
    digitalWrite(relaywaterlevelhighPUMP, HIGH);
    }
    else if(sensorValue>=100){
     digitalWrite(relaywaterlevellowPUMP, HIGH);
    digitalWrite(relaywaterlevelhighPUMP, LOW);
    }
}

void firebaseReconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    digitalWrite(res, LOW);
    delay(500);
    digitalWrite(res, HIGH);
    Serial.println("Restarting Connection");
    delay(1000);
  }




