#ifndef IO_INPUT_H
#define IO_INPUT_H

#include "Arduino.h"
#include "IO_inputs_cfg.h"
#include "SharedDatatype.h"

class IOinput
{
    public:
        void InitInputs(void);
        void FastCyclic(SharedData_t *SharedData);

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

        IOInputs_ShiftUpRequest_type IOInputs_ShiftUpRequest;
        IOInputs_ShiftDownRequest_type IOInputs_ShiftDownRequest; 
};

#endif