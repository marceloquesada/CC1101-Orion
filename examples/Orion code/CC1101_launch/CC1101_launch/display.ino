
// Creation of display object
Adafruit_SSD1306 display(128, 32, &Wire, -1);

// Initialization the the OLED display for printing debug messgaes (abreviated versions of messages from serial) 
void displayInit()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Display address allocation failed, check connection."));
  }
  Serial.println("Display successfully initialized.");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.display();
}

void displayLine(String line)
{
  if (!SCREEN_ENABLED) {
    return;
  }
  
  //This condition checks if all display lines have been filled, if so, it clears the display and starts back in first position
  if (display.getCursorY() >= 32) {
    display.clearDisplay();
    display.setCursor(0, 0);
  }

  // This line prints the log time of the message in seconds since ESP bootup and then the message
  display.println(String(millis()/1000) + "> " + line);
  Serial.println("Internal display: " + String(millis()/1000) + "> " + line);
  display.display();
}