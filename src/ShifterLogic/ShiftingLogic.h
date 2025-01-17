#ifndef SHIFTING_LOGIC_H
#define SHIFTING_LOGIC_H

// Class declaration for model ShiftingLogic
class ShiftingLogic final
{
  // public data and function members
 public:

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  ShiftingLogic();

  // Destructor
  ~ShiftingLogic();

  // private data and function members
 private:
  uint8_t current_gear;
};


#endif                                


