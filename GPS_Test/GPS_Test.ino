#include "WSLib.h"
#define GPS_SERIAL Serial2
SdGps gps(&GPS_SERIAL);
#define hallInPin 8
#define DSEL 12


void setup() {
  pinMode(12,INPUT);
  //Serial2.begin(9600);
  pinMode(hallInPin,INPUT);
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);
  pinMode(46,OUTPUT);
  pinMode(46,LOW);
  
  Serial.begin(9600); 
  Serial.print("all good so far...");
  delay(2000);
  
  uint8_t errorByte = 0x00;
  if( !gps.Setup() ){
    Serial.println(F("Error initializing GPS!"));
    errorByte += 0x08;
  }
  else{
    Serial.println(F("GPS initialized."));
  } 

}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial2.available());
{
  int temp = Serial2.read();
  Serial.print(temp);
}
}
