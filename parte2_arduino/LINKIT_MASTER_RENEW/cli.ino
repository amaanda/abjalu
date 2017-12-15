const unsigned int CLI_MAX_BUFFER = 24;
const char CLI_START_CHAR = 'c';
const char CLI_IGNORED_CHAR = '-';
const char CLI_END_CHAR = '\r';

bool cli_decoding = false;
String cli_command = "";
unsigned int cli_pointer = 0;

void runCLI(char c) {

  if( cli_decoding && c != CLI_IGNORED_CHAR ) {

    if( c == CLI_END_CHAR || cli_pointer > CLI_MAX_BUFFER ) {
      
      cli_execute(cli_command);
      cli_pointer = 0;
      cli_command = "";
      cli_decoding = false;
      
    } else if( c != '\r' || c != '\n' ) {
      
      cli_pointer++;
      cli_command+=c;
      
    }

  }

  if( c == CLI_START_CHAR ) {
    cli_decoding = true;
    cli_pointer = 0;
  }

}

void cli_execute(String command) {
  if( command == "ping" )
    sayLinkit("linkit_pong!");
  
  else if( command == "pingslave" )
    saySlave("c-ping");

  else if( command == "pingzero" )
    saySlave("c-pingzero");

  else if( command == "pingone" )
    saySlave("c-pingone");

  else if( command == "autoping" )
    autoping();

  else 
    sayLinkit("UNKNOW COMMAND");
}

