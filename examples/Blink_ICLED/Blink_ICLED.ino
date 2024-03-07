#include <WLICLED_SPI.h>

void setup() {
  // put your setup code here, to run once:
  WLICLED.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WLICLED.setICLED(1, 0xFF, 0xFF, 0xFF);
  WLICLED.show();
  delay(500); 
}
