
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

void setup()
{
  //usbComm.Init();
  
  UIHandlerInit();
  IOinput_Obj.InitInputs();
  ShiftingLogic_Obj.initialize();
  Serial.begin(115200);
  delay(1000);
  USBCommInit();
}

void setup1() 
{
  //UIHandlerInit();  
  
  
}

void loop()
{
  
  UIHandlerCyclic(&SharedData);
  IOinput_Obj.FastCyclic(&SharedData);
  Serial.println(SharedData.ShiftUpRequest);
  ShiftingLogic_Obj.step(&SharedData);
  USBCommCyclic(&SharedData);
  delay(15);
}

void loop1() 
{
  
  
  //delay(100);
}