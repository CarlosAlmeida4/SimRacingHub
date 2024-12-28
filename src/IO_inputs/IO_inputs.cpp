#include "Arduino.h"
#include "IO_inputs\IO_inputs.h"

static uint8_t oldMaxGearDown = 0;
static uint8_t oldMaxGearUp = 0;

void IOinput::InitInputs()
{
    IOInputs_MaxGearLimit.MaxGearDownPin = MAXGEARDOWN_PIN;
    IOInputs_MaxGearLimit.MaxGearUpPin = MAXGEARUP_PIN;
    IOInputs_ShiftUpRequest.ShiftUpRequestPin = SHIFTUPREQUEST_PIN;
    IOInputs_ShiftDownRequest.ShiftDownRequestPin = SHIFTDOWNREQUEST_PIN;
    IOInputs_ResetCount.ResetCountPin = RESETCOUNT_PIN;

    pinMode(IOInputs_MaxGearLimit.MaxGearDownPin,INPUT);
    pinMode(IOInputs_MaxGearLimit.MaxGearUpPin,INPUT);
    pinMode(IOInputs_ShiftUpRequest.ShiftUpRequestPin,INPUT_PULLUP);
    pinMode(IOInputs_ShiftDownRequest.ShiftDownRequestPin,INPUT_PULLUP);
    pinMode(IOInputs_ResetCount.ResetCountPin,INPUT);

    IOInputs_ShiftUpRequest.ShiftUpRequest = 0;
    IOInputs_ShiftDownRequest.ShiftDownRequest = 0;
    IOInputs_ResetCount.ResetCount = 0;

    oldMaxGearDown = digitalRead(IOInputs_MaxGearLimit.MaxGearDownPin);
    oldMaxGearUp = digitalRead(IOInputs_MaxGearLimit.MaxGearDownPin);
}

void IOinput::FastCyclic()
{
    IOInputs_ShiftUpRequest.ShiftUpRequest = !digitalRead(IOInputs_ShiftUpRequest.ShiftUpRequestPin);
    IOInputs_ShiftDownRequest.ShiftDownRequest = !digitalRead(IOInputs_ShiftDownRequest.ShiftDownRequestPin);
    IOInputs_ResetCount.ResetCount = digitalRead(IOInputs_ResetCount.ResetCountPin);
    IOInputs_MaxGearLimit.MaxGearLimitUp = digitalRead(IOInputs_MaxGearLimit.MaxGearUpPin);
    IOInputs_MaxGearLimit.MaxGearLimitDown = digitalRead(IOInputs_MaxGearLimit.MaxGearDownPin);
    //Serial.print("Shit Up Request : ");
    //Serial.println(IOInputs_ShiftUpRequest.ShiftUpRequest);
    //Serial.print("Shit Down Request : ");
    //Serial.println(IOInputs_ShiftDownRequest.ShiftDownRequest);
}