
#include "Arduino.h"
#include "UIHandler\UIHandler.h"
#include "USBComm\USBComm.h"
#include "IO_inputs\IO_inputs.h"
#include "ShifterLogic\ShiftingLogic.h"  
#include "SharedDatatype.h" //TODO Evaluate if implementing a Mediator class is helpful

//#define MAIN_DEBUG_1

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
  Serial.begin(115200);
  delay(3000);
  USBCommInit();
}

void setup1() 
{
  ShiftingLogic_Obj.initialize();
  delay(2000);
  USBCommInit();
}

void loop()
{
  IOinput_Obj.FastCyclic(&SharedData);
  #ifdef MAIN_DEBUG
  Serial.println("Ran IO Input");
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

  UIHandlerCyclic(&SharedData);
  #ifdef MAIN_DEBUG_1
  Serial.println("Ran UI Handler");
  #endif
  ShiftingLogic_Obj.step(&SharedData);
  #ifdef MAIN_DEBUG_1
  Serial.println("Ran Shifting logic Handler");
  #endif
  #ifdef MAIN_DEBUG_1
  Serial.println("SharedData:");
  Serial.print("SharedData.CurrentGear ");
  Serial.println(SharedData.CurrentGear);
  Serial.print("SharedData.ShiftUpRequest ");
  Serial.println(SharedData.ShiftUpRequest);
  Serial.print("SharedData.ShiftDownRequest ");
  Serial.println(SharedData.ShiftDownRequest);
  #endif
  //delay(100);
}