#ifndef SHARED_DATA_TYPE_H
#define SHARED_DATA_TYPE_H

#include "Arduino.h"

typedef volatile struct SharedDatatype
{
    uint8_t ShiftUpRequest;
    uint8_t ShiftDownRequest;
    uint8_t CurrentGear;
}SharedData_t;

#endif