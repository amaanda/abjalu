#include <SoftwareSerial.h>

SoftwareSerial rs485_serial(RS485_RX_PIN, RS485_TX_PIN, false, RS485_BUFFER); // RS485 Serial
bool rs485_is_reading = false;

void rs485_setup() {
  pinMode(RS485_DIRECTION_PIN, OUTPUT);
  rs485_readMode();

  rs485_serial.begin(RS485_BAUD);
  rs485_clear();
}

void rs485_run() {
  if(rs485_is_reading) {

    if( rs485_serial.available() > 0 ) {
      char c = rs485_serial.read();
      if(c != -1) {

        cli_takeChar(c);

        protocol_takeChar(c);

        server_takeCharAndBroadcast(c);

      }
    }

  }
}

void rs485_readMode() {
  digitalWrite(RS485_DIRECTION_PIN, RS485_READ_MODE);
  rs485_is_reading = true;
}

void rs485_writeMode() {
  rs485_is_reading = false;
  digitalWrite(RS485_DIRECTION_PIN, RS485_WRITE_MODE);
}

void rs485_clear() {
  while(rs485_serial.available()) {
    rs485_serial.read();
  }
  rs485_serial.flush();
}

void rs485_sayMaster(String s) {
  rs485_writeMode();
  delay(10);
  rs485_serial.println(s);
  rs485_serial.flush();
  delay(3);
  rs485_readMode();
}

int rs485_broad_pointer = 0;
String rs485_broadcast_msg = "";
void rs485_takeCharAndBroadcast(char c) {

  if(rs485_broad_pointer > 0) {

    rs485_broadcast_msg+=c;
    rs485_broad_pointer++;

    if(rs485_broad_pointer==5) {
      rs485_broad_pointer = 0;
      rs485_sayMaster(rs485_broadcast_msg);
    }

  }

  if(c=='a') {
    rs485_broad_pointer = 1;
    rs485_broadcast_msg = "";
    rs485_broadcast_msg+=PROTOCOL_START_CHAR;
  }

}
