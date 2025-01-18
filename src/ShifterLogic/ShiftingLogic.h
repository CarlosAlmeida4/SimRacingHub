#ifndef SHIFTING_LOGIC_H
#define SHIFTING_LOGIC_H

#include "Arduino.h"
#include "SharedDatatype.h"

// Class declaration for model ShiftingLogic
class ShiftingLogic final
{
  // public data and function members
  public:

  // model initialize function
  void initialize();

  // model step function
  void step(SharedData_t *SharedData);

};

#endif                                


