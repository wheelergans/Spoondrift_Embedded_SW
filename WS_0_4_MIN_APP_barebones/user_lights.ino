#define USER_LED_TIME 300000 //time user leds will remain active after power up or hall trigger
//\todo: different types of light sequences for different types of errors
bool idleLedsActive = false;
bool startupLedSeqActive = false;
bool chargeLedSeqActive = false;
bool chargingActive = false;
bool statSetupError = false;
bool sdMissingError = false;
bool powSetupError = false;
bool solSetupError = false;
int killTimerIndex = -1;

void startUserLedSeq( uint8_t errorByte ){
  idleLedsActive = false;
  chargeLedSeqActive = false;  
  drifterBoard.statLedOff();
  drifterBoard.powLedOff();
  if( errorByte & 0xFF ){
    if( errorByte & ~0x01 ){ //Error bit set other than SD missing (RED ERROR)
      statSetupError = true;
    }
    else{
      sdMissingError = true; //Only SD missing bit is set (ORANGE ERROR)
    }
  }
  if( powerSetupErrorByte > 0 ){
    if(powerSetupErrorByte & ~0x10){ //if an error bit is set *other* than the solar bit, go red.
      powSetupError = true;

    }
    else{ //otherwise only solar bit, go orange.
      solSetupError = true;
    }
  }
  startupLedSeqActive = true;
  if( killTimerIndex > -1 ){
    simpleTimer.deleteTimer( killTimerIndex ); //timer already active from a previous mode switch
  }
  killTimerIndex = simpleTimer.setTimeout( USER_LED_TIME, killStartupSeq );
  flashUserLeds();
}

void startIdleLedSeq(){
  startupLedSeqActive = false;
  chargeLedSeqActive = false;
  idleLedsActive = true;
  drifterBoard.statLedOff();
  drifterBoard.powLedOff();
  if( killTimerIndex > -1 ){
    simpleTimer.deleteTimer( killTimerIndex ); //timer already active from a previous mode switch
  }
  killTimerIndex = simpleTimer.setTimeout( USER_LED_TIME, killStartupSeq );
  idleLedPulse();
}

void killStartupSeq( void ){
  killTimerIndex = -1;
  startupLedSeqActive = false;
  idleLedsActive = false;
  statSetupError = false;
  powSetupError = false;
  solSetupError = false;
  drifterBoard.powLedOff();
  drifterBoard.statLedOff();
  if( !chargeLedSeqActive ){ //could already be active from a kill timer from previous mode
    chargeLedSeqActive = true;
    startChargingLedTimer(); 
  }
}

void flashUserLeds( void ){
  if( !startupLedSeqActive ){
    drifterBoard.powLedOff();
    drifterBoard.powLedOff();
    return;
  }
  if( powSetupError ){
    drifterBoard.powLedRed();
  }
  else if( solSetupError ){
    drifterBoard.powLedOrange();
  }
  else{
    drifterBoard.powLedGreen();
  }
  if( statSetupError ){
    drifterBoard.statLedRed();
  }
  else if( sdMissingError ){
    drifterBoard.statLedOrange();
  }
  else{
    drifterBoard.statLedGreen();
  }
  simpleTimer.setTimeout( 100, startFlashTimer );
}

void startFlashTimer(){
  drifterBoard.statLedOff();
  drifterBoard.powLedOff();
  if( startupLedSeqActive ){
    simpleTimer.setTimeout( 300, flashUserLeds );
  }
}

void idleLedPulse(){
  static bool toggler = false;
  if( !idleLedsActive ){
    drifterBoard.statLedOff();
    drifterBoard.powLedOff();
    return;
  }
  if( toggler ){
    drifterBoard.statLedGreen();
    drifterBoard.powLedOff();
  }
  else{
    drifterBoard.statLedOff();
    drifterBoard.powLedGreen();
  }
  toggler = !toggler;
  simpleTimer.setTimeout( 400, idleLedPulse );
}

void startChargingLedTimer(){
  if( !chargeLedSeqActive ){
    drifterBoard.powLedOff();
    return;
  }
  charge_stat_t chargeStatus = powerBoard.getChargeStatus();
  if ( chargeStatus == CHARGE_COMPLETE && powerBoard.dcInput ){ //if battery is charged and dc connected, stays solid
    drifterBoard.powLedGreen();
  }
  else{
    drifterBoard.powLedOff();
  }
  simpleTimer.setTimeout(500,flashChargingLeds);
}

void flashChargingLeds(){
  if( !chargeLedSeqActive ){
    drifterBoard.powLedOff();
    return;
  }
  //if DC connected pulse light
  if(powerBoard.dcInput){
    drifterBoard.powLedGreen();
  }
  else{
    drifterBoard.powLedOff();
  }
  simpleTimer.setTimeout(100,startChargingLedTimer);
}









