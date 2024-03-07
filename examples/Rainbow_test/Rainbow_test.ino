/*Blink_ICLED
 * 
 * Description:   This program is used to create a smoth color change on an ICLED
 * Notes:         For ICLED there is no standard chip (LED) layout, so the color combinations between models can vary such as: GRB, RGB, BGR, etc. 
 *                In view of this, the order of the variables is defined as first, second and third chip (regarding the LED layout)
 *                Overal brightness is set to 50% for eyesafety; for 100% change the brightness level from 0x80 to 0xFF
 *                Do not directly look into the ICLED without proper protection
 * 
 * 
 * 
 * Version:       1.0
 * Date:          14.12.2023
 * Created by:    Carlos Roberto Hernandez Gomez
 * 
 */

#include <Arduino.h>
#include <WLICLED_SPI.h>

#define NUM_ICLEDS  1
WLICLED pixel(NUM_ICLEDS);

void setup() {
  pixel.beginSPI();
  pixel.clear();      //  The loop is initialized to 0
  pixel.show();       //  Latch this information to the ICLED strip 
}

void loop() 
{
    for(int i = 0; i<256, i++)
    {
      pixel.setICLED(1, i, 0x00, 0x00, 0x80);       //Instruction to define the color (ICLED number, First chip, Second chip, Third chip, Brightness)
      pixel.show();                                 //Instruction to send this information to the ICLED
      delay(15);  
    }

    delay(500);

    for(int i = 0; i<256, i++)
    {
      pixel.setICLED(1, 255-i, i, 0x00, 0x80);      //Instruction to define the color (ICLED number, First chip, Second chip, Third chip, Brightness)
      pixel.show();                                 //Instruction to send this information to the ICLED
      delay(15);  
    }

    delay(500);
    
    for(int i = 0; i<256, i++)
    {
      pixel.setICLED(1, 0x00, 255-i, i, 0x80);      //Instruction to define the color (ICLED number, First chip, Second chip, Third chip, Brightness)
      pixel.show();                                 //Instruction to send this information to the ICLED
      delay(15);  
    }

    delay(500);
    
    for(int i = 0; i<256, i++)
    {
      pixel.setICLED(1, i, 0xFF, 255-i, 0x80);      //Instruction to define the color (ICLED number, First chip, Second chip, Third chip, Brightness)
      pixel.show();                                 //Instruction to send this information to the ICLED
      delay(15);  
    }

    delay(500);
}
