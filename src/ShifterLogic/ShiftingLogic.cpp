#include "Arduino.h"
#include "ShiftingLogic.h"

// Model step function
void ShiftingLogic::step(SharedData_t *SharedData)
{
  static uint8_t oldShiftUpRequest = 0, oldShiftDownRequest = 0;
  if(SharedData->ShiftUpRequest == 1 && oldShiftUpRequest == 0)
  {
    
  } 
  oldShiftUpRequest = SharedData->ShiftUpRequest;
  if(SharedData->ShiftDownRequest == 1 && oldShiftDownRequest == 0)
  {
    
  } 
  oldShiftDownRequest = SharedData->ShiftDownRequest;

}

// Model initialize function
void ShiftingLogic::initialize()
{

}



