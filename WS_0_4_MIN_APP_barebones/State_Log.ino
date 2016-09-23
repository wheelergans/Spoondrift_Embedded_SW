#define STATE_LOG_ERROR_LEVEL 0x01

SdLog stateLog((const char *)"%s_SYS.CSV", (const char *)"millis,time,EVENT TYPE, EVENT DETAIL" );

enum ERR_TYPE{
  POWER_SETUP_ERROR, GPS_SETUP_ERROR, XTEND_SETUP_ERROR};

uint8_t stateLogLevel = 0x01;

//void logError( ERR_TYPE errorType, uint8_t errorCode ){
//
//}
