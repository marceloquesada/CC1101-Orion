
Adafruit_BMP280 bmp;

void baromInit(){
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
  if (!status) {
    displayLine("BAR READ ERROR");
    delay(10000); // Timeto warn user about barometer malfunction
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
  }
}

void baromTest(){
  float pressure = bmp.readPressure();
  float temperature = bmp.readTemperature();
  displayLine(("T:" + String(temperature) + "ºC P:" + String(pressure)));
}

void getAltitude(){
  
}