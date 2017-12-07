String command = "";

void runCLI(char c) {

  if(c >= 32 && c <= 126 && c != '\r' && c != '\n')
    command += c;

  if( c == '\r' || c == '\n' ) {
    digitalWrite(ledPin, HIGH);
    executeCommand(command);
    command = "";
  }
    
}

void executeCommand(String command) {  
  if( command == "ping" ) {
    digitalWrite(ledPin, HIGH);
    sayMaster("slave_pong");
  }
  
  //else if( command == "ping_slave" )
    //saySlave("ping");
}

