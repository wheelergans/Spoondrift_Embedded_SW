#define hallInPin 8
int pollMagnet( void ){
 // delayMicroseconds( 27 ); //max poweron time + max out rise time of A1126LUA-T
  int retVal = digitalRead( hallInPin );
  return retVal;
}

void setup() {
  pinMode(hallInPin,INPUT);
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);
  pinMode(46,OUTPUT);
  pinMode(46,LOW);
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("begin");
}

void loop() {
  Serial.println(pollMagnet());
  delay(500);
  // put your main code here, to run repeatedly:

}
