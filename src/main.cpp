
#include "Arduino.h"
#include "UIHandler\UIHandler.h"
#include "USBComm\USBComm.h"
#include "IO_inputs\IO_inputs.h"

IOinput main_IOinput;

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
  main_IOinput.InitInputs();  
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
  main_IOinput.FastCyclic();
}

void loop() 
{
  USBCommCyclic();
  delay(100);
}