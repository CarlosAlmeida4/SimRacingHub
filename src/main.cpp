
#include "Arduino.h"
#include "UIHandler\UIHandler.h"
#include "USBComm\USBComm.h"
#include "IO_inputs\IO_inputs.h"
#include "ShifterLogic\ShiftingLogic.h"  

IOinput IOinput_Obj;
ShiftingLogic ShiftingLogic_Obj;

/*********************
*        MAIN        *
**********************/

void setup1()
{
  //usbComm.Init();
  UIHandlerInit();
  IOinput_Obj.InitInputs();
  //ShiftingLogic_Obj.initialize();
  delay(1000);
}

void setup() 
{
  //UIHandlerInit();  
  USBCommInit();
  Serial.begin(115200);
}

void loop1()
{
  //USBCommCyclicHandler(nullptr);
  UIHandlerCyclic();
  IOinput_Obj.FastCyclic();
  //ShiftingLogic_Obj.step();
}

void loop() 
{
  USBCommCyclic();
  
  delay(100);
}