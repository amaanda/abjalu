/*
 *  RS485 PROJECT
 *
 *  SLAVE ONE BOARD - NODEMCU
 */

void setup() {

  hardware_setup();

  serial_setup();

  wifi_setup();

  wifi_connect();

  ota_setup();

  rs485_setup();

  server_setup();

  hardware_ledOn();

  serial_clear();

}

void loop() {

  wifi_run();

  ota_run();

  rs485_run();

  server_run();

  hardware_workingSignal();

}
