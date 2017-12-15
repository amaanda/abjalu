#include <ESP8266WiFi.h>

WiFiServer server(SERVER_TELNET_PORT);
WiFiClient serverClients[SERVER_MAX_CLIENTS];

void server_setup() {
  //start UART and the server
  server.begin();
  server.setNoDelay(true);

  serial_debug("Ready! Use 'telnet ");
  serial_debug( String( WiFi.localIP() ) );
  serial_debug(" 23' to connect");
}

void server_run() {

  server_checkNewClients();

  server_checkDataFromClients();

  server_checkDataFromSerial();

}

void server_checkNewClients() {
  if (server.hasClient()){
    for(uint8_t i = 0; i < SERVER_MAX_CLIENTS; i++){
      //find free/disconnected spot
      if (!serverClients[i] || !serverClients[i].connected()){
        if(serverClients[i]) serverClients[i].stop();
        serverClients[i] = server.available();
        serial_debug("New client: "); serial_debug(String(i));
        continue;
      }
    }
    //no free/disconnected spot so reject
    WiFiClient serverClient = server.available();
    serverClient.stop();
  }
}

void server_checkDataFromClients() {
  for(uint8_t i = 0; i < SERVER_MAX_CLIENTS; i++){
    if (serverClients[i] && serverClients[i].connected()){
      if(serverClients[i].available()){
        //get data from the telnet client and push it to the UART
        while(serverClients[i].available()) {
          char c = char( serverClients[i].read() );
          protocol_takeChar(c);
          rs485_takeCharAndBroadcast(c);
        }
      }
    }
  }
}

void server_checkDataFromSerial() {
  if(Serial.available()){
    size_t len = Serial.available();
    uint8_t sbuf[len];
    Serial.readBytes(sbuf, len);
    //push UART data to all connected telnet clients
    for(uint8_t i = 0; i < SERVER_MAX_CLIENTS; i++){
      if (serverClients[i] && serverClients[i].connected()){
        serverClients[i].write(sbuf, len);
        delay(1);
      }
    }
  }
}

void server_sayMaster(String s) {
  //push UART data to all connected telnet clients
  for(uint8_t i = 0; i < SERVER_MAX_CLIENTS; i++){
    if (serverClients[i] && serverClients[i].connected()) {
      serverClients[i].println(s);
      delay(1);
    }
  }
}

int server_broad_pointer = 0;
String server_broadcast_msg = "";
void server_takeCharAndBroadcast(char c) {

  if(server_broad_pointer > 0) {

    server_broadcast_msg+=c;
    server_broad_pointer++;

    if(server_broad_pointer==5) {
      server_broad_pointer = 0;
      server_sayMaster(server_broadcast_msg);
    }

  }

  if(c=='a') {
    server_broad_pointer = 1;
    server_broadcast_msg = "";
    server_broadcast_msg+=PROTOCOL_START_CHAR;
  }

}
