/* Benjamin Aigner, 2022 <beni@asterics-foundation.org> */
/* Public domain / CC 0 */

/** example code using all possibilities of the Joystick class
 * for the RP2040.
 */

#include "Joystick\Joystick.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Use BOOTSEL to start the Joystick demo.");
  Joystick.begin();
}

void loop() {
  if (BOOTSEL) {
    Joystick.setButton(2,true);
		delay(500);
		Joystick.setButton(2,false);
		delay(500); //we need a short delay here, sending packets with less than 1ms leads to packet loss!
	  Serial.println("Joystick buttons");
    /*for(uint8_t i = 0; i<32; i++)
    {
    Serial.print("Button: ");
    Serial.println(i);
		Joystick.setButton(i,true);
		delay(500);
		Joystick.setButton(i,false);
		delay(500); //we need a short delay here, sending packets with less than 1ms leads to packet loss!
	  }*/
	//alternativ with manual send:
	/*Joystick.useManualSend(true);
	Serial.println("Joystick buttons - manual send");
    for(uint8_t i = 1; i<=32; i++)
    {
		Joystick.button(i,true);
		Joystick.send_now();
		delay(250);
		Joystick.button(i,false);
	}
	Joystick.useManualSend(false);*/
  }
}
