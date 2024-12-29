
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

void setup() 
{
  Serial.begin(115200);
  UIHandlerInit();
}
void setup1()
{
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
}

void loop() {
  UIHandlerCyclic();
}

void loop1()
{

}