
#include "Arduino.h"
#include "UIHandler\UIHandler.h"
#include "USBComm\USBComm.h"
#include "IO_inputs\IO_inputs.h"
#include "ShifterLogic\ShiftingLogic.h"  
#include "SharedDatatype.h" //TODO Evaluate if implementing a Mediator class is helpful

/*********************
*Object Instantiation*
**********************/
IOinput IOinput_Obj;
ShiftingLogic ShiftingLogic_Obj;

/*********************
*     Shared Data    *
**********************/
SharedData_t SharedData;

/*********************
*        MAIN        *
**********************/

void setup1()
{
  //usbComm.Init();
  UIHandlerInit();
  IOinput_Obj.InitInputs();
  ShiftingLogic_Obj.initialize();
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
  UIHandlerCyclic(&SharedData);
  IOinput_Obj.FastCyclic(&SharedData);
  ShiftingLogic_Obj.step(&SharedData);
}

void loop() 
{
  USBCommCyclic(&SharedData);
  
  //delay(100);
}