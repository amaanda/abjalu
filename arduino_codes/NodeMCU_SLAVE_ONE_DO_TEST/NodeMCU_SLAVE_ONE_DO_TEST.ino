/*
 *  RS485 PROJECT 
 * 
 *  SLAVE ONE BOARD - NODEMCU
 */

/*
 *  Definitions for Sensor and Relay
 */
#define sensorPin A0 // Sensor of board
#define loadPin 5 // Relay of board
#define ledPin 16 // Working Probe Led

/*
 *  Definitions for RS485 COM
 */ 
#define directionPin 0 // used to enable/disable RX/TX in MAX485
#define rxPin 13 // rx pin in software serial
#define txPin 15 // tx pin in software serial
#define READING LOW
#define WRITING HIGH
#define RS_BAUD 9600
#define RS_BUFFER 256


/* 
 *  For RS485 COM
 */
#include <SoftwareSerial.h>

//SoftwareSerial rsSerial(rxPin, txPin, false, RS_BUFFER); // RS485 Serial

void setup() {
  setupOta();

  /*
   * Basic BOARD SETUP
   */
  pinMode(sensorPin, INPUT);
  
  pinMode(loadPin, OUTPUT);
  digitalWrite(loadPin, LOW);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  setupFlow();

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  digitalWrite(txPin, LOW);
  
  //rsSerial.begin(RS_BAUD);
  //while(rsSerial.available()) {
    //rsSerial.read();
  //}
  //rsSerial.flush();
}


void doTest() {
  writeMode();
  digitalWrite(txPin, HIGH);
  delay(2000);
  digitalWrite(txPin, LOW);
  delay(2000);
  readMode(); 
}


void loop() {
  runOta();

  doTest();

  //runFlow();
  //sayMaster("ping ");
  //delay(30);
  digitalWrite(ledPin, LOW);   // turn the LED for get to know it is working
}
