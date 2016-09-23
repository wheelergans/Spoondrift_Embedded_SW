#define ENABLE_TOP_LIGHT
#define TOP_LIGHT_PERIOD 2500
#define TOP_LIGHT_PULSE 150

bool topLightActive = false;

void startTopLight(void){
  topLightActive = true;
  pulseTopLight();
}

void stopTopLight(){
  drifterBoard.extLedOff();
  topLightActive = false;
}

void pulseTopLight(void){
  if( !topLightActive ){
    return;
  }
#ifdef ENABLE_TOP_LIGHT
  drifterBoard.extLedOn();
#endif
  simpleTimer.setTimeout( TOP_LIGHT_PULSE, resetTopLight );
}

void resetTopLight(void){
  drifterBoard.extLedOff();
  if( !topLightActive ){
    return;
  }
  simpleTimer.setTimeout( TOP_LIGHT_PERIOD, pulseTopLight );
}


