const char BOARD_ADDRESS = '1';

/*  
 * PROTOCOL
 * 
 * sample:
 *
 * 0AR -> read board 0 sensor
 * 1AR -> read board 1 sensor
 *
 * 0A1S -> set relay for board 0 to ON (1)
 * 1A0S -> set relay for board 1 to OFF (0)
 */

void sayMaster(String s) {
  writeMode();
  delay(500);
  rsSerial.println(s);
  rsSerial.flush();
  delay(5);
  readMode();
}

const char ADDRESS = 'a';
const char READ = 'r';
const char SET = 's';

char destination = 'n';
char lastByte = 'n';

void runProtocol(char c) {
  if(c != -1) {

    if(c == ADDRESS)
      destination = lastByte;
    
    if(destination == BOARD_ADDRESS) {
    
      if(c == READ)
        readOperation();
      
      if(c == SET)
        writeOperation(lastByte);
 
    }

    lastByte = c;      
    
  }
}

void readOperation() { 
  String msg = "" + analogRead(A0);
  sayMaster(msg);
}

void writeOperation(char value) {
  if( value == '1')
    digitalWrite(loadPin, HIGH);
  else
    digitalWrite(loadPin, LOW);
}

