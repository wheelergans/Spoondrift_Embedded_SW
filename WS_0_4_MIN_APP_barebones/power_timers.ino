#define LOG_INTERVAL 30000
#define SAMPLE_INTERVAL 2000
#define SWEEP_INTERVAL 300000 

void startPowerTimers(){
  simpleTimer.setInterval( LOG_INTERVAL, runPowerLog );
  simpleTimer.setInterval( SAMPLE_INTERVAL,runPowerSample );
  simpleTimer.setInterval( SWEEP_INTERVAL, runPowerSweep );
}

void runPowerLog(){
  float hum, temp;
  drifterBoard.readHumTemp( hum, temp );
  powerBoard.calcAverages();
  powerBoard.updateChargeStatus();
  powerBoard.logPowerData( hum, temp );
}
void runPowerSample(){
  powerBoard.updatePowerData();
}

void runPowerSweep(){
  powerBoard.sweepEnable();  
}
