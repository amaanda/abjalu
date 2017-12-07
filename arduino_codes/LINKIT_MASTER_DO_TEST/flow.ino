bool IS_READING = false;

void setupFlow() {
  pinMode(directionPin, OUTPUT);
  readMode();
}

void runFlow() {

  if( Serial1.available() > 0 ) {
    char c = Serial1.read();
    if(c != -1) {
        
      runCLI(c);
      //runProtocol(c);
       
    }
  }
  
  if(IS_READING)
    readRS();
}

void readMode() {
  IS_READING = true;
  digitalWrite(directionPin, READING);
}

void writeMode() {
  IS_READING = false;
  digitalWrite(directionPin, WRITING);
}

/* 
 *  Listen To Responses
 */
void readRS() {
//  if( rsSerial.available() > 0 ) {
//    char c = rsSerial.read(); // read from RS 485
//    if(c != -1)
//      Serial1.write(c);   // just bridge the readings up stairs
//  }
}

