#ifndef IO_INPUT_H
#define IO_INPUT_H

#include "Arduino.h"

#define MAXGEARUP_PIN 4
#define MAXGEARDOWN_PIN 3
#define SHIFTUPREQUEST_PIN 7
#define SHIFTDOWNREQUEST_PIN 6
#define RESETCOUNT_PIN 5
#define MAXGEARDEFAULT_VALUE 6

class IOinput
{
    public:
        void InitInputs(void);
        void FastCyclic(void);
        struct IOInputs_ResetCount_type
        {
            uint8_t ResetCountPin;
            uint8_t ResetCount;

        };
        struct IOInputs_MaxGearLimit_type
        {
            uint8_t MaxGearUpPin;
            uint8_t MaxGearDownPin;
            uint8_t MaxGearLimitUp;
            uint8_t MaxGearLimitDown;
        };
        struct IOInputs_ShiftUpRequest_type
        {
            uint8_t ShiftUpRequestPin;
            uint8_t ShiftUpRequest;
        };
        struct IOInputs_ShiftDownRequest_type
        {
            uint8_t ShiftDownRequestPin;
            uint8_t ShiftDownRequest;
        };

                
        IOInputs_MaxGearLimit_type IOInputs_MaxGearLimit;
        IOInputs_ShiftUpRequest_type IOInputs_ShiftUpRequest;
        IOInputs_ShiftDownRequest_type IOInputs_ShiftDownRequest; 
        IOInputs_ResetCount_type IOInputs_ResetCount;
};

#endif