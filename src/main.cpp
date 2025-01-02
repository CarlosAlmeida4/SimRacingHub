
#include "Arduino.h"
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include "UIHandler\UIHandler.h"
#include "USBComm\USBComm.h"

TaskHandle_t SerialCommHandle;
USBComm usbComm;

std::map<eTaskState, const char *> eTaskStateName { {eReady, "Ready"}, { eRunning, "Running" }, {eBlocked, "Blocked"}, {eSuspended, "Suspended"}, {eDeleted, "Deleted"} };
void ps() {
  int tasks = uxTaskGetNumberOfTasks();
  TaskStatus_t *pxTaskStatusArray = new TaskStatus_t[tasks];
  unsigned long runtime;
  tasks = uxTaskGetSystemState( pxTaskStatusArray, tasks, &runtime );
  Serial.printf("# Tasks: %d\n", tasks);
  Serial.println("ID, NAME, STATE, PRIO, CYCLES");
  for (int i=0; i < tasks; i++) {
    Serial.printf("%d: %-16s %-10s %d %lu\n", i, pxTaskStatusArray[i].pcTaskName, eTaskStateName[pxTaskStatusArray[i].eCurrentState], (int)pxTaskStatusArray[i].uxCurrentPriority, pxTaskStatusArray[i].ulRunTimeCounter);
  }
  delete[] pxTaskStatusArray;
}

/*********************
*       TASKS        *
**********************/

void USBCommCyclicHandler(void *param)
{
  while(1)
  {
    (void) param;
    TickType_t currentTime = pdTICKS_TO_MS(xTaskGetTickCount());
    usbComm.Cyclic();
    delay(100);
  }
}

void UIHandlerCyclic(TimerHandle_t timer)
{

}

void SerialCommHandler(void *param)
{
  while(1)
  {
    (void) param;
    TickType_t currentTime = pdTICKS_TO_MS(xTaskGetTickCount());
    String a;
    if(Serial.available() > 0)
    {
      a = Serial.readString();
      // say what you got:
      Serial.print("I received: ");
      Serial.println(a);
    }
    Serial.print(" SerialCommHandler took: ");
    Serial.println((pdTICKS_TO_MS(xTaskGetTickCount()) - currentTime));
    delay(1000);
    //
  }
}

/*********************
*        MAIN        *
**********************/

void setup1()
{
  Serial.begin(115200);
  usbComm.Init();
  TaskHandle_t USBCommTaskHandle;
  //TimerHandle_t USBCommTaskTimer = xTimerCreate("USB_COM_TIMER",pdMS_TO_TICKS(USBCOMM_TIMER_PERIOD_MS),pdTRUE,USBCOMM_TIMER_ID,USBCommCyclicHandler);
  xTaskCreate(USBCommCyclicHandler,"USBCOMMCYCLICHANDLER",1024,nullptr,1,&USBCommTaskHandle);
  //xTaskCreate(SerialCommHandler,"SerialCommHandler",1024,nullptr,2,&SerialCommHandle);
  delay(1000);
  //vTaskStartScheduler();
}

void setup() 
{
  UIHandlerInit();  
}

void loop1()
{
  ps();
}

void loop() 
{
  UIHandlerCyclic();  
}