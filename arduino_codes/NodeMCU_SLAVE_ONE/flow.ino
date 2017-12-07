bool IS_READING = false;

void setupFlow() {
  pinMode(directionPin, OUTPUT);
  readMode();
}

void runFlow() {
  if(IS_READING) {
    if( rsSerial.available() > 0 ) { 
      char c = rsSerial.read();
      if(c != -1) {
             
          runCLI(c);
          runProtocol(c);  
        
      }
    }
  }
}

void readMode() {
  IS_READING = true;
  digitalWrite(directionPin, READING);
}

void writeMode() {
  IS_READING = false;
  digitalWrite(directionPin, WRITING);
}
