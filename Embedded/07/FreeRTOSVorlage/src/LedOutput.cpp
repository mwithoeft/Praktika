#include <Energia.h>
#include "OutputStrategy.h"

const uint8_t LedPortOut = RED_LED;
class LedOutput : public OutputStrategy{
  public:
    LedOutput(const uint8_t LedPortOut)
    :OutputStrategy(LedPortOut){}
};
