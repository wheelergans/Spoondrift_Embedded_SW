/*
 * Fallback timer for GPS
 * 
 * The interrupt should go off every 1.1seconds, but only if the GPS fails to 
 * work.
 *
 */
#define FALLBACK_PERIOD 1100000

static bool GpsFallbackTimerEvent = false;
static uint8_t GpsFallbackTimerCount = 0;

uint8_t GetGpsFallbackTimerCount() { 
  return GpsFallbackTimerCount; 
}

bool GetGpsFallbackTimerEvent() { 
  return GpsFallbackTimerEvent; 
}

void ResetGpsFallbackTimerCount() { 
  GpsFallbackTimerCount = 0; 
  GpsFallbackTimerEvent = false; 
}

void ResetGpsFallbackTimerEvent() { 
  GpsFallbackTimerEvent = false; 
}

void GpsFallbackTimer_Handler(void){
  GpsFallbackTimerEvent = true; //set timer event flag in ISR
  GpsFallbackTimerCount++;
}

void setupFallbackTimer(void){
  Timer3.initialize(FALLBACK_PERIOD); // Initialize GPS fallback timer for 1.1seconds
  Timer3.attachInterrupt(GpsFallbackTimer_Handler, FALLBACK_PERIOD);
}

