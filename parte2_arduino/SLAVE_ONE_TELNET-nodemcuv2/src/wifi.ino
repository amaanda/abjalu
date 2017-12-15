#include <ESP8266WiFi.h>

void wifi_setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
}

void wifi_run() {
  wifi_check();
}

bool wifi_connected = false;

void wifi_connect() {
  serial_debug("\nConnecting to "); serial_debug(WIFI_SSID);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  if(i == 21){
    serial_debug("Could not connect to"); serial_debug(WIFI_SSID);
    hardware_errorSignal();
  } else {
    wifi_connected = true;
  }
}

void wifi_check() {
  if( wifi_shouldCheck() ) {
    if(WiFi.status() != WL_CONNECTED) {
      wifi_connected = false;
      hardware_errorSignal();
    }
  }
}

unsigned long wifi_last_check = 0;

bool wifi_shouldCheck() {
  unsigned long now = millis();
  unsigned long past_time = now - wifi_last_check;

  if( past_time > WIFI_CHECK_TIME ) {
    wifi_last_check = now;
    return true;
  }

  // prevents millis reset (aproximately each 50 days for arduino uno
  if(wifi_last_check > now)
    wifi_last_check = now;

  return false;
}

bool wifi_isConnected() {
  return wifi_connected;
}
