void extMagOn(){
  Serial.println(F("magnet on."));
  switch( currentOpMode ){
  case OP_MODE_RUN:
    Serial.println(F("SWITCH TO IDLE MODE."));
    currentOpMode = OP_MODE_IDLE;
    rom.setOpMode( currentOpMode );
    idle_setup();
    incSessionId();
    break;
  case OP_MODE_IDLE:
    Serial.println(F("SWITCH TO RUN MODE."));
    currentOpMode = OP_MODE_RUN;
    rom.setOpMode( currentOpMode );
    run_setup();
    incSessionId();
    break;
  default:
    Serial.println(F("CURRENT MODE INVALID!"));
    //todo: resetMe();
    break;    
  }
}

void extMagOff(){
  Serial.println(F("magnet off."));
}

void incSessionId(){
  sessionId = rom.incSessionId();
  Serial.print(F("Inc sessionId to "));
  Serial.println(sessionId);
  SdLog::SdLogSetupDirectory( sessionId );
}
