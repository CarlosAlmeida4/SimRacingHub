
#include "Arduino.h"
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include "UIHandler\UIHandler.h"
#include "USBComm\USBComm.h"

#define USBCOMM_TIMER_PERIOD_MS 1000
#define USBCOMM_TIMER_ID 0

TaskHandle_t USBCommTaskHandle;
USBComm usbComm;

void USBCommCyclicHandler(TimerHandle_t timer)
{
  usbComm.Cyclic();
}

void setup1() 
{
  Serial.begin(115200);

  usbComm.Init();
  TimerHandle_t USBCommTaskTimer = xTimerCreate("USB_COM_TIMER",pdMS_TO_TICKS(USBCOMM_TIMER_PERIOD_MS),pdTRUE,USBCOMM_TIMER_ID,USBCommCyclicHandler);
  if(USBCommTaskTimer != nullptr)
  {
    xTimerStart(USBCommTaskTimer,0);
  }
  else
  {
    // TODO: Handle this case
  }
  //vTaskStartScheduler();
}
void setup()
{
  UIHandlerInit(); 
}

String a;


void loop1() {
  
  if(Serial.available() > 0)
  {
    a = Serial.readString();
    // say what you got:
    Serial.print("I received: ");
    Serial.println(a);
  }
}

void loop()
{
  UIHandlerCyclic();
}