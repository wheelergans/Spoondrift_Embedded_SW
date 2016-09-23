#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>

#include "WSLib.h"

//#define RF_SERIAL Serial1
#define GPS_SERIAL Serial2
#define DSEL 12

//DigiXtend Xtend(&RF_SERIAL, 0x7000);  //destination address of receiver is 0x7000
SdGps gps(&GPS_SERIAL);
SdEeprom rom;
DrifterBoard drifterBoard(Serial);
PowerBoard powerBoard;
//DataSender dataSender( gps, Xtend );

SimpleTimer simpleTimer;

uint8_t startupErrorByte = 0x00;
uint8_t powerSetupErrorByte = 0x00;
uint16_t sessionId = 0;
WS_OP_MODE currentOpMode = OP_MODE_INVALID;

void setup(){
  pinMode(DSEL,INPUT);
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);
  pinMode(46,OUTPUT);
  pinMode(46,LOW);
  
  Serial.begin(57600);
  Serial.println(F(""));
  Serial.println(F("*************************"));
  Serial.println(F("Initializing WaveSpotter RF 0.5"));
  drifterBoard.begin();
  rom.Init();
  sessionId = rom.incSessionId();
  Serial.print(F("  Session ")); 
  Serial.println( sessionId );
  drifterBoard.VDDSDOn();
  delay(20);
  Serial.print(F("Initializing SD Card: "));
  uint8_t sdError = SdLog::Setup( sessionId ); //run this once to initialize the SD card
  SdLog::setExceedCb( SDFileExceed_cb );
  if( sdError == 0x00 ){
    Serial.println(F("SUCCESS."));
  }
  else if( sdError == 0x01 ){
    Serial.println(F("Card not present!"));
  }
  else if( sdError == 0x02 ){
    Serial.println(F("Card failed!"));
  }
  else if( sdError == 0x03 ){
    Serial.println(F("SD directory setup failed!"));
  }
  else{
    Serial.println(F("UNHANDLED SD RETURN CODE !FIXME!"));
  }
  startupErrorByte += sdError;
  powerSetupErrorByte = powerBoard.Setup();
  currentOpMode = rom.readOpMode();
  Serial.print(F("Loaded OP MODE: "));
  switch( currentOpMode ){
  case OP_MODE_RUN:
    Serial.println(F("RUN"));
    run_setup();
    break;
  case OP_MODE_IDLE:
    Serial.println(F("IDLE"));
    idle_setup();
    break;
  default:
    Serial.println(F("INVALID!"));
    startupErrorByte += 0x10;
    //todo: re-write run mode, resetMe();
    break;    
  }
  Serial.print(F("Startup error byte: ")); 
  Serial.println(startupErrorByte, HEX);
  Serial.print(F("Power error byte: ")); 
  Serial.println(powerSetupErrorByte, HEX);
  //TODO: print decoding of error bytes
  startPowerTimers();
  Serial.println(F( "WaveSpotter setup complete." ));
  Serial.println(F("*************************"));
}
// Main program loop 
void loop(){
  switch( currentOpMode ){
    
  case OP_MODE_RUN:
    run_tasks();
    break;
  case OP_MODE_IDLE:
    idle_tasks();
    break;
  default:
    //todo: resetMe();
    break;    
  }
  drifterBoard.run();
  simpleTimer.run();
}

void SDFileExceed_cb( uint32_t fileSize, uint32_t accessTime ){
  Serial.println(F("Log file exceeded!"));
  Serial.print( fileSize ); 
  Serial.print( F( "  file access time: " ) ); 
  Serial.println( accessTime );
  sessionId = rom.incSessionId();
  Serial.print(F("Inc sessionId to "));
  Serial.println(sessionId);
  SdLog::SdLogSetupDirectory( sessionId );
}







