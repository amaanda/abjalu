void serial_setup() {
  if(SERIAL_DEBUG) {
    Serial.begin(SERIAL_BAUD);
    serial_clear();
  }
}

void serial_clear() {
  if(SERIAL_DEBUG) {
    Serial.println("");
    Serial.println("-- SERIAL CLEAR --");
    Serial.println("");
  }
}

void serial_debug(String str) {
  if(SERIAL_DEBUG)
    Serial.println(str);
}
