String command = "";

void runCLI(char c) {
  if(c != '\r')
    command += c;
  else {
    executeCommand(command);
    command = "";
  }
}

void executeCommand(String command) {  
  if( command == "ping" )
    sayLinkit("linkit_pong!");
  
  else if( command == "ping_slave" )
    saySlave("ping");

  else if( command == "autoping" )
    autoping();
  
  else 
    sayLinkit("UNKNOW COMMAND");
}

