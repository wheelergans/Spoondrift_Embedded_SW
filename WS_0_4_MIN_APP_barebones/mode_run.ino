//********************************************************//
// Setup tasks only for run mode
uint8_t run_setup(){
  drifterBoard.statLedOrange();
  drifterBoard.powLedOrange();
  uint8_t errorByte = startupErrorByte;
  drifterBoard.VDD5VOff();
  drifterBoard.VDDGPSOff();
  delay(20);
  drifterBoard.VDD5VOn();
  delay(20);
  /*
  if( !Xtend.Setup() ){
    Serial.println(F("Error initializing xtend!"));
    errorByte += 0x04;
  }
  else{
    Serial.println(F("Xtend initialized."));
  }*/
  drifterBoard.VDDGPSOn();
  delay(20);
  if( !gps.Setup() ){
    Serial.println(F("Error initializing GPS!"));
    errorByte += 0x08;
  }
  else{
    Serial.println(F("GPS initialized."));
  }
  gps.Update();
  gps.EnableLogging( true );
  
  delay(20);
  //\todo: retrieve log levels from EEPROM
  setupFallbackTimer();
  startTopLight();
  startUserLedSeq( errorByte );
  //dataSender.Setup();
  return errorByte;
}

//********************************************************//
//main loop tasks only for run mode
bool run_tasks(){
  //Xtend.Update();
  gps.Update();  
  /*if( dataSender.run( powerBoard.battLowFlag) ){
    return true;
  }*/
  //todo: check fallbacktimer status, send SOS for help if necessary
  return false;
}





