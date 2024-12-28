
#include "Arduino.h"
#include <FreeRTOS.h>
#include "UIHandler\UIHandler.h"
#include "USBComm\USBComm.h"

USBComm usbComm;

void setup() {
  Serial.begin(115200);
  
  Serial.println("Adafruit TinyUSB HID Gamepad example");
  
  UIHandlerInit();
}

void setup1()
{
  usbComm.Init();
}

void loop() {
  UIHandlerCyclic();
}

void loop1()
{
  usbComm.Cyclic();
}