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

void sayLinkit(String s) { // to LINKIT 
  Serial1.println(s);
}

void saySlave(String s) {
  writeMode();
  delay(5);
//  rsSerial.println(s);
//  rsSerial.flush();
  delay(3);
  readMode();
}


const char ADDRESS = 'a';
const char READ = 'r';
const char SET = 's';

char destination = 'n';
char lastByte = 'n';

void runProtocol(char c) {

  if(c == ADDRESS)
    destination = lastByte;
  
  if(c == READ)
    readOperation(destination);
    
  if(c == SET)
    writeOperation(destination, lastByte);

  lastByte = c;
}

void readOperation(char destination) {
  sayLinkit("READING ");
  String msg = "";
  msg+=destination;
  msg+=ADDRESS;
  msg+=READ;
  sayLinkit(msg);
  saySlave(msg);
}

void writeOperation(char destination, char value) { 
  sayLinkit("WRITING");
  String msg = "";
  msg+=destination;
  msg+=ADDRESS;
  msg+=value;
  msg+=SET;
  sayLinkit(msg);
  saySlave(msg);
}
