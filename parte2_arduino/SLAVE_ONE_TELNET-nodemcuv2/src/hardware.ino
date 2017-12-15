
void hardware_setup() {
  hardware_setupSensor();
  hardware_setupRelay();
  hardware_setupLed();
}

void hardware_setupSensor() {
  pinMode(HARDWARE_SENSOR_PIN, INPUT);
}

char hardware_readSensor() {
  int val = analogRead(HARDWARE_SENSOR_PIN)/4;
  return char(byte(val));
}

void hardware_setupRelay() {
  pinMode(HARDWARE_RELAY_PIN, OUTPUT);
  hardware_relayOff();
}

void hardware_relayOn() {
  digitalWrite(HARDWARE_RELAY_PIN, HARDWARE_RELAY_ON);
}

void hardware_relayOff() {
  digitalWrite(HARDWARE_RELAY_PIN, HARDWARE_RELAY_OFF);
}

void hardware_relayShift() {
  boolean state_to_put_relay = !digitalRead(HARDWARE_RELAY_PIN);
  digitalWrite(HARDWARE_RELAY_PIN, state_to_put_relay);
}

void hardware_setupLed() {
  pinMode(HARDWARE_LED_PIN, OUTPUT);
  hardware_ledOff();
}

void hardware_ledOn() {
  digitalWrite(HARDWARE_LED_PIN, HARDWARE_LED_ON);
}

void hardware_ledOff() {
  digitalWrite(HARDWARE_LED_PIN, HARDWARE_LED_OFF);
}

void hardware_ledShift() {
  boolean state_to_put_led = !digitalRead(HARDWARE_LED_PIN);
  digitalWrite(HARDWARE_LED_PIN, state_to_put_led);
}

void hardware_workingSignal() {

  if( hardware_shouldPulseWorkingSignal() )
    hardware_ledShift();

}

void hardware_errorSignal() {

  while(1) {
      hardware_ledShift();
      delay(HARDWARE_ERROR_SIGNAL_TIME); // ms
  }

}

void hardware_debugSignal() {
  hardware_ledOn();
  delay(HARDWARE_DEBUG_SIGNAL_TIME);
}

unsigned long hardware_last_signal = 0;

bool hardware_shouldPulseWorkingSignal() {
  unsigned long now = millis();
  unsigned long past_time = now - hardware_last_signal;

  if( past_time > HARDWARE_WORKING_SIGNAL_TIME ) {
    hardware_last_signal = now;
    return true;
  }

  // prevents millis reset (aproximately each 50 days for arduino uno)
  if(hardware_last_signal > now)
    hardware_last_signal = now;

  return false;
}
