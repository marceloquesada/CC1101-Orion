#include <CC1101_Orion.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>


#define GDO0 4       // Pino da conexão GDO0
#define VPIN A0       // Pino do check de tensão

#define SCREEN_ENABLED true
#define MSG_INTERV 5000    // Delay between messages, in ms

#define USE_RELATIVE_ALTITUDE true // This variable controls if the altitude is relative to sea level or ground level
#define GROUND_ALTITUDE 546        // Ground elevation, in meters

bool comm_status = true;

int time_ref;
int interval;

char payload[] = "Orion project, by: Lau Mar Mur Math Alic";

byte packet[60];

void setup() {
  Wire.begin(21, 22);
  
  //Serial.begin(9600);
  if (SCREEN_ENABLED) {
    displayInit();
  }
  CCinit(10);
  baromInit();
}

void loop() {
  sendPacket();
  delay(MSG_INTERV);  // Change to timer later
}
