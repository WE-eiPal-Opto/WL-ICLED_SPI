#include "WLICLED_SPI.h"

/*!
  @brief  Initializes the WLICLED object, sets the number of ICLEDs and allocates memory for the LED data buffer based on this number.
  @param[in]  numICLEDs Number of ICLEDs used in the circuit
*/
WLICLED::WLICLED(uint16_t numICLEDs)
{
  _numICLEDs = numICLEDs;
  _ICLEDBuff = new byte[_numICLEDs*3*8];                    // 
  clear();                                                  // Initialize the LED buffer with all LEDs Off
}


/*!
  @brief  Frees the memory allocated for the LED data buffer.
*/

WLICLED::~WLICLED()
{
  delete[] _ICLEDBuff;                          //Free allocated memory
}



/*!
  @brief  Function to initialize the SPI and configures the SPI settings like clock speed, bit order, and data mode (suitable for ICLED communication)
*/
void WLICLED::beginSPI()
{
  SPI.begin();                                                      
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE1)); // Sets the SPI clock to the half the frequency of the system clock / Clock polarity = 0; Clock phase = 1; Output edge = Rising; Data capture = Falling;
}



/*!
  @brief  Cleans up SPI settings and releases resources.
*/
void WLICLED::endSPI()
{
  SPI.endTransaction();
}



/*!
  @brief Updates the LED data buffer with color and brightness of the ICLED selected. The show(); function is later needed to send out this information.
  @param[in]  N ICLED to be controlled (starting from 1)
  @param[in]  G 8-bit PWM value for green chip
  @param[in]  R 8-bit PWM value for the red chip
  @param[in]  B 8-bit PWM value for the blue chip 
  @param[in]  Bright  8-bit value for the overal brightness level of the ICLED

*/
void WLICLED::setICLED(uint16_t N, uint8_t G, uint8_t R, uint8_t B, uint8_t Bright)
{
  updateBuffer(N, G, R, B, Bright);
}



void WLICLED::updateBuffer(uint16_t N, uint8_t G, uint8_t R, uint8_t B, uint8_t Bright)
{
  // Check that the input values are under the established limits (0xFF or 255)
    Bright = (Bright > MAX_BRIGHTNESS) ? MAX_BRIGHTNESS : Bright;
    G = (G > MAX_PWM) ? MAX_PWM : G;
    R = (R > MAX_PWM) ? MAX_PWM : R;
    B = (B > MAX_PWM) ? MAX_PWM : B;

  //Array to hold the corrected PWM values (after brightness scaling)
    uint8_t colors[3] = {((G * Bright) / MAX_BRIGHTNESS), ((R * Bright) / MAX_BRIGHTNESS), ((B * Bright) / MAX_BRIGHTNESS)};
    uint16_t ICLEDCode = (N - 1) * 24;                      //BitMask lenght equals 24 bytes per LED (8 for each color)

  //Coding of the PWM (color) into the bit pattern for SPI transmission
    for (int color = 0; color < 3; color++) 
    {
        uint8_t colorValue = colors[color];
        for (int bit = 0; bit < 8; bit++) 
        {
            //_ICLEDBuff[index++], the value of ICLED_index is used for array indexing first, and only then is it incremented.
            _ICLEDBuff[ICLEDCode++] = (colorValue & 0x80) ? 0b11111110 : 0b11100000;        //  Values tested for Arduino UNO, only change this if the user knows what he is doing
            colorValue <<= 1;
        }
    }
}



/*!
  @brief  Transmits the LED data buffer to the ICLEDs. 
  @return None
*/
void WLICLED::show()
{
  noInterrupts();
  SPI.transfer(_ICLEDBuff, _numICLEDs * 3 * 8);           // Transfer the entire information buffer (_ICLEDBuff)
  interrupts();
  delayMicroseconds(200);                             //Reset code for ICLEDs
}



/*!
  @brief   Set the defined color information for all ICLEDs in the declared circuit
  @param[in]   G  8 bit color value for Green
  @param[in]   R  8 bit color value for Red
  @param[in]   B  8 bit color value for Blue
  @param[in]   Bright 8-bit value for the overal brightness level of the ICLED
*/
void WLICLED::fill(uint8_t G, uint8_t R, uint8_t B, uint8_t Bright)
{ // Display a single color on the defined amount of IC LEDs
    for (uint16_t i = 0; i < _numICLEDs; i++) {
        updateBuffer(i+1, G, R, B, Bright);
    }
} // End of setStrip



/*!
  @brief   Set all the information in the ICLED Buffer to 0 (ICLEDs OFF)
  @return  None
*/
void WLICLED::clear()
{ // Set all LEDs in the buffer to 0x000000 (Off)
  for (uint16_t i = 0; i < _numICLEDs; i++) {
        updateBuffer(i+1, 0, 0, 0, 0);
    }
} 