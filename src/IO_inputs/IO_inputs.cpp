#include "Arduino.h"
#include "IO_inputs\IO_inputs.h"

static uint8_t oldMaxGearDown = 0;
static uint8_t oldMaxGearUp = 0;

void IOinput::InitInputs()
{
    IOInputs_ShiftUpRequest.ShiftUpRequestPin = SHIFTUPREQUEST_PIN;
    IOInputs_ShiftDownRequest.ShiftDownRequestPin = SHIFTDOWNREQUEST_PIN;
    
    pinMode(IOInputs_ShiftUpRequest.ShiftUpRequestPin,INPUT_PULLUP);
    pinMode(IOInputs_ShiftDownRequest.ShiftDownRequestPin,INPUT_PULLUP);

    IOInputs_ShiftUpRequest.ShiftUpRequest = 0;
    IOInputs_ShiftDownRequest.ShiftDownRequest = 0;
}

void IOinput::FastCyclic(SharedData_t *SharedData)
{
    IOInputs_ShiftUpRequest.ShiftUpRequest = !digitalRead(IOInputs_ShiftUpRequest.ShiftUpRequestPin);
    IOInputs_ShiftDownRequest.ShiftDownRequest = !digitalRead(IOInputs_ShiftDownRequest.ShiftDownRequestPin);
    SharedData->ShiftDownRequest = IOInputs_ShiftDownRequest.ShiftDownRequest;
    SharedData->ShiftUpRequest = IOInputs_ShiftUpRequest.ShiftUpRequest;
    //serial.print("Shit Up Request : ");
    //serial.println(IOInputs_ShiftUpRequest.ShiftUpRequest);
    //serial.print("Shit Down Request : ");
    //serial.println(IOInputs_ShiftDownRequest.ShiftDownRequest);
}