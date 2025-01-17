
#include "Arduino.h"
#include "UIHandler\UIHandler.h"
#include "USBComm\USBComm.h"
#include "ShifterLogic\ShiftingLogic.h"  

static ShiftingLogic ShiftingLogic_Obj;

/*********************
*       TASKS        *
**********************/

void USBCommCyclicHandler(void *param)
{
  while(1)
  {
    (void) param;
    //usbComm.Cyclic();
    delay(100);
  }
}

void UIHandlerCyclicHandler(void *param)
{
  while(1)
  {
    UIHandlerCyclic();
    delay(10);
  }
}

/*********************
*        MAIN        *
**********************/

void setup1()
{
  //usbComm.Init();
  UIHandlerInit();  
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
  UIHandlerCyclic();
  
  
}

void loop() 
{
  USBCommCyclic();
  delay(100);
}