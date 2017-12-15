const unsigned int PROTOCOL_MAX_BUFFER = 5;
const char PROTOCOL_START_CHAR = 'a';
const char PROTOCOL_READ_CHAR = 'r';
const char PROTOCOL_SET_CHAR = 's';

bool protocol_decoding = false;
unsigned int protocol_pointer = 0;

char protocol_destination = 'n';
char protocol_op = 'n';
char protocol_value = 'n';
unsigned char protocol_cs = 'n';

void protocol_takeChar(char c) {

  if( protocol_decoding ) {

    if( protocol_pointer == 0 ) {
      protocol_destination = c;
      protocol_pointer++;
    } else if( protocol_pointer == 1 ) {
      protocol_op = c;
      protocol_pointer++;
    } else if( protocol_pointer == 2 ) {
      protocol_value = c;
      protocol_pointer++;
    } else if ( protocol_pointer == 3 ) {
      protocol_cs = c;
      protocol_executeIfOk();
      protocol_decoding = false;
    }

  } else if( c == PROTOCOL_START_CHAR ) {
    protocol_decoding = true;
    protocol_pointer = 0;
  }

}

void protocol_executeIfOk() {

  String msg = "";
  msg+=PROTOCOL_START_CHAR;
  msg+=protocol_destination;
  msg+=protocol_op;
  msg+=protocol_value;

  if( protocol_cs ==  protocol_errorCharacterFor(msg) ) {

    if(protocol_destination == BOARD_ADDRESS) {

      if(protocol_op == PROTOCOL_READ_CHAR) {

        op_read();

      } else if(protocol_op == PROTOCOL_SET_CHAR) {

        op_write(protocol_value);

      }

    }

  }

}

void protocol_execute(String command) {
  if( command == "ping" ) {
    //hardware_debugSignal();
    rs485_sayMaster("slave_pong");
  }

  else if( command == "ping"+BOARD_ADDRESS_STRING ) {
    //hardware_debugSignal();
    rs485_sayMaster("slave_pong_from_"+BOARD_ADDRESS_STRING);
  }

  //else if( command == "ping_slave" )
    //saySlave("ping");
}

char protocol_errorCharacterFor(String msg) {
  byte cks = 0;

  for(int i=0; i < 4; i++) {
    cks += byte(msg[i]);
  }

  //return char(cks);
  return 'l';
}
