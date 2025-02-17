
#include "Arduino.h"
#include "UIHandler\UIHandler.h"
#include "USBComm\USBComm.h"
#include "IO_inputs\IO_inputs.h"
#include "ShifterLogic\ShiftingLogic.h"  
#include "SharedDatatype.h" //TODO Evaluate if implementing a Mediator class is helpful

#define MAIN_DEBUG

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
  #ifdef MAIN_DEBUG
  Serial.println("Ran UI Handler");
  #endif
  IOinput_Obj.FastCyclic(&SharedData);
  #ifdef MAIN_DEBUG
  Serial.println("Ran IO Input");
  #endif
  ShiftingLogic_Obj.step(&SharedData);
  #ifdef MAIN_DEBUG
  Serial.println("Ran Shifting logic Handler");
  #endif
  USBCommCyclic(&SharedData);
  #ifdef MAIN_DEBUG
  Serial.println("Ran USB CommCyclic");
  #endif
  //delay(15);
  #ifdef MAIN_DEBUG
  Serial.println("SharedData:");
  Serial.print("SharedData.CurrentGear ");
  Serial.println(SharedData.CurrentGear);
  Serial.print("SharedData.ShiftUpRequest ");
  Serial.println(SharedData.ShiftUpRequest);
  Serial.print("SharedData.ShiftDownRequest ");
  Serial.println(SharedData.ShiftDownRequest);
  #endif
}

void loop1() 
{
  
  
  //delay(100);
}