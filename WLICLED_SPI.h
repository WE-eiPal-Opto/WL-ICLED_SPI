#ifndef WLICLED_SPI
#define WLICLED_SPI

#include <SPI.h>

#define MAX_PWM  255
#define MAX_BRIGHTNESS  255

class WLICLED
{
public:
    WLICLED(uint16_t numICLEDs);
    ~WLICLED();                                                              

  void beginSPI();                                                                // System configuration to enable SPI data transmission
  
  void endSPI();                                                                  // System configuration to disable SPI data transmission
  
  void setICLED (uint16_t N, uint8_t G, uint8_t R, uint8_t B, uint8_t Bright); 
  
  void fill(uint8_t G, uint8_t R, uint8_t B, uint8_t Bright);                     // Define the color and brightness information for all ICLEDs in the circuit (numICLEDs)
  
  void show();
  
  void clear();

private:
   uint16_t _numICLEDs; 
  
   byte* _ICLEDBuff;                                                              // Buffer to hold ICLED data
  
   void updateBuffer (uint16_t N, uint8_t G, uint8_t R, uint8_t B, uint8_t Bright);
};
#endif