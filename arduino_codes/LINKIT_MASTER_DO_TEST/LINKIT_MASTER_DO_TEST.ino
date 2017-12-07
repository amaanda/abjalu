/*
 *  RS485 PROJECT 
 * 
 *  MASTER BOARD - LINKIT SMART DUO
 */

#define ledPin 13 // Working Probe Led

#define LINKIT_BAUD 9600

/*
 *  Definitions for RS485 COM
 */ 
#define directionPin 5 // used to enable/disable RX/TX in MAX485
#define rxPin 9 // rx pin in software serial
#define txPin 8 // tx pin in software serial
#define READING LOW
#define WRITING HIGH
#define RS_BAUD 9600
#define RS_BUFFER 256

/* 
 *  For RS485 COM
 */
#include <SoftwareSerial.h>
//SoftwareSerial rsSerial(rxPin, txPin);

void setup()
{
  Serial1.begin(LINKIT_BAUD); // open internal serial connection to MT7688AN // in MT7688AN, this maps to device
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  setupFlow();

  pinMode(rxPin, INPUT);
  pinMode(txPin, INPUT);

  //rsSerial.begin(RS_BAUD);
  //while(rsSerial.available())
    //rsSerial.read();
 //rsSerial.flush();
}

void doTest() {
  //writeMode();
  //digitalWrite(txPin, HIGH);
  //delay(2000);
  //digitalWrite(txPin, LOW);
  //delay(2000);
  Serial1.print(digitalRead(rxPin));
  Serial1.print(", ");
  Serial1.println(digitalRead(txPin));
  delay(200);
  readMode(); 
}

void loop()
{
  /* 
   *  Listen To Responses
   */
  //runFlow();

  doTest();

  //runAuto();

  digitalWrite(ledPin, HIGH);   // turn the LED for get to know it is working
}

