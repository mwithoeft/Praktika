#include <Energia.h>
#include "OutputStrategy.h"


OutputStrategy::OutputStrategy(const uint8_t pin)
	: outputPin(pin){
	pinMode(outputPin, OUTPUT);
}

void OutputStrategy::printMorse(char character){
	if(character == '-'){
		digitalWrite(outputPin, HIGH);
		delay(Dah);
		digitalWrite(outputPin, LOW);
		delay(Dit);
	}else if(character == '.'){
		digitalWrite(outputPin, HIGH);
		delay(Dit);
		digitalWrite(outputPin, LOW);
		delay(Dit);
	}
}
OutputStrategy& OutputStrategy::operator=(const OutputStrategy &other){
	if(this != &other){
		this->outputPin = other.outputPin;
	}
	return *this;
}

