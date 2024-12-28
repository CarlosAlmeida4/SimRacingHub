#ifndef IO_OUTPUT_H
#define IO_OUTPUT_H

#include "Arduino.h"

#define LED1PIN 8
#define LED2PIN 9
#define LED3PIN 10
#define LED4PIN 21
#define LED5PIN 0
#define LED6PIN 1
#define LED7PIN 2
#define LED8PIN 20

#define NLEDS 8

class IOoutput {

    private:    
        //uint8_t IOOutputPin[NLEDS];


        struct OutputState_t {
          uint8_t Outport[NLEDS];                // '<Root>/Outport'
        };

    public:
    void InitOutputs(void);
    void FastCyclic(uint8_t outputState[]);
};

#endif
