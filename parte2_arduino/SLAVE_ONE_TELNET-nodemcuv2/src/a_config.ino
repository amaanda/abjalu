const char BOARD_ADDRESS = '1';
const String BOARD_ADDRESS_STRING = "one";

#define SERIAL_DEBUG false

//how many clients should be able to telnet to this ESP8266
#define SERVER_TELNET_PORT 23
#define SERVER_MAX_CLIENTS 1

#define SERIAL_BAUD 9600 // Working Probe Led

const char* WIFI_SSID = "linkit";
const char* WIFI_PSWD = "linkit123";
#define WIFI_CHECK_TIME 3000

// in milliseconds
#define HARDWARE_WORKING_SIGNAL_TIME 1000
#define HARDWARE_ERROR_SIGNAL_TIME 300
#define HARDWARE_DEBUG_SIGNAL_TIME 3000

#define HARDWARE_LED_PIN 16 // Working Probe Led
#define HARDWARE_LED_OFF HIGH // Working Probe Led
#define HARDWARE_LED_ON LOW // Working Probe Led

#define HARDWARE_SENSOR_PIN A0 // Sensor of board
#define HARDWARE_RELAY_PIN 5 // Relay of board
#define HARDWARE_RELAY_OFF LOW //
#define HARDWARE_RELAY_ON HIGH //

#define RS485_DIRECTION_PIN 0 // used to enable/disable RX/TX in MAX485
#define RS485_READ_MODE LOW
#define RS485_WRITE_MODE HIGH

#define RS485_RX_PIN 13 // rx pin in software serial
#define RS485_TX_PIN 15 // tx pin in software serial

#define RS485_BAUD 9600
#define RS485_BUFFER 256

const char* OTA_HOSTNAME = "SLAVE_ONE_esp8266";
