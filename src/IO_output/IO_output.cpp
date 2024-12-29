#include "Arduino.h"
#include "IO_output\IO_output.h"

static uint8_t IOOutputPin[] = {
            LED1PIN,
            LED2PIN,
            LED3PIN,
            LED4PIN,
            LED5PIN,
            LED6PIN,
            LED7PIN,
            LED8PIN,
        };

void IOoutput::InitOutputs()
{

    for(int i = 0; i< NLEDS; i++)
    {
        pinMode(IOOutputPin[i],OUTPUT);
    }
}

void IOoutput::FastCyclic(uint8_t outputState [])
{
    for(int i = 0; i< NLEDS; i++)
    {
        digitalWrite(IOOutputPin[i],outputState[i]);

    }
}