#include "Arduino.h"
#include "ShiftingLogic.h"

//#define SHIFT_DEBUG

// Model step function
void ShiftingLogic::step(SharedData_t *SharedData)
{
  static uint8_t oldShiftUpRequest = 0, oldShiftDownRequest = 0;

  if(SharedData->ShiftUpRequest == 1 && oldShiftUpRequest == 0)/* Rising edge */
  {
    #ifdef SHIFT_DEBUG
    Serial.println("Shift Up");
    #endif
    USBCommSetButtonReport(SHIFTUP_GAMEPAD);
  }
  else if (SharedData->ShiftUpRequest == 0 && oldShiftUpRequest == 1)/* Faling edge */
  {
    USBCommResetButtonReport(SHIFTUP_GAMEPAD);
  }
  
  oldShiftUpRequest = SharedData->ShiftUpRequest;

  if(SharedData->ShiftDownRequest == 1 && oldShiftDownRequest == 0)/* Rising edge */
  {
    #ifdef SHIFT_DEBUG
    Serial.println("Shift Down");
    #endif
    USBCommSetButtonReport(SHIFTDOWN_GAMEPAD);
  }
  else if (SharedData->ShiftDownRequest == 0 && oldShiftDownRequest == 1)/* Faling edge */
  {
    USBCommResetButtonReport(SHIFTDOWN_GAMEPAD);
  } 

  oldShiftDownRequest = SharedData->ShiftDownRequest;
}

// Model initialize function
void ShiftingLogic::initialize()
{

}



