#include <Energia.h>
#include "OutputStrategy.h"

const uint8_t BuzzerPortOut = PC_6;

class BuzzerOutput : public OutputStrategy{
  public:
    BuzzerOutput(const uint8_t BuzzerPortOut)
    :OutputStrategy(BuzzerPortOut){}
};
