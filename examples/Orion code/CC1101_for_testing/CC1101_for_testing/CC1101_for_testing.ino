#include <CC1101_Orion.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>

#define GDO0 2       // Pino da conexão GDO0
#define VPIN A0       // Pino do check de tensão

#define SCREEN_ENABLED true

// AJUSTABLE VARIABLES
#define TX_TYPE 0     // 0 FOR CONSTANT PREAMBLE TRANSMISSION, 1 FOR TEST STRING
#define DELAY 200000    // Time between transmissions in ms
#define TxPower 10    // Options are: -30  -20  -15  -10  -6   0   5   7   10, only for 915mhz: 11, 12

int time_ref;
int interval;

byte tx_msg[60];

void setup() {
  Wire.begin(4, 5);

  fillPacket(TX_TYPE);
  
  displayInit();
  CCinit();
}

void loop() {
  sendPacket();
  delay(DELAY);
}
