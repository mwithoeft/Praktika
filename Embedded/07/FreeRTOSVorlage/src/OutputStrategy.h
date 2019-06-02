#ifndef OutputStrategy_H
#define OutputStrategy_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Energia.h>
//delay between signals characters
const uint16_t Dit = 500;
//delay between characters
const uint16_t Dah = Dit * 3;
//delay between wordds
const uint16_t WordDelay = Dit * 7;

class OutputStrategy
{
public:
	OutputStrategy(const uint8_t pin);
	void printMorse(char character);
	OutputStrategy& operator=(const OutputStrategy &other);
protected:
	uint8_t outputPin;
};
#ifdef __cplusplus
}
#endif
#endif
