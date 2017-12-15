void op_read() {
  char sensor = hardware_readSensor();

  String msg = "";
  msg+='s';
  msg+=BOARD_ADDRESS;
  msg+='r';
  msg+=sensor;
  msg+=protocol_errorCharacterFor( msg );
  
  rs485_sayMaster(msg);
  server_sayMaster(msg);
}

void op_write(char value) {
  if( value == '1')
    hardware_relayOn();
  else
    hardware_relayOff();
}
