#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>
#include "WSLib.h"


uint8_t powerSetupErrorByte = 0x00;
PowerBoard powerBoard;

void setup() {

  Serial.begin(9600);
  Serial.println("Serial begun");

powerSetupErrorByte = powerBoard.Setup();

for(int i=0;i<128;++i)
{
    Wire.beginTransmission( i );
    int a= Wire.endTransmission();
    if(a != 2)
    {
      Serial.print("address = ");Serial.println(i);
    }
}
delay(20);


 


  // put your setup code here, to run once:

}

void loop() {
  powerBoard.updateChargeStatus();
  powerBoard.dumpPowerData();
  //delay(3000);
  //put your main code here, to run repeatedly:

//Serial.println(Wire.requestFrom( 47, 1 )); 
//int value = Wire.read();
//Serial.print("register value = ");Serial.println(value);
delay(20);
}



