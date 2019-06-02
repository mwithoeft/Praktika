#include "inc/tm4c123gh6pm.h" 
#include "driverlib/interrupt.h" 
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

const int SerialRate = 9600; 

const uint8_t BuzzerPortOut = PC_6;
const uint8_t ButtonPin4 = PC_4;
const uint8_t ButtonPin5 = PC_5;

const byte buttonstate_released = 0;
const byte buttonstate_pressed = 1;
const byte buttonstate_held = 2;
const byte buttonstate_is_released = 3;

int stateD = 0;
int stateB = 0;


template <const uint8_t PIN_NB>
class TButton {
public:
  TButton(){
    pinMode(PIN_NB, INPUT);
    }
    int state(){
      int state = digitalRead(PIN_NB);
    
      if(state != lastButtonState) {
          lastDebounceTime = millis();
      }
      
      if ((millis( ) - lastDebounceTime) > debounceDelay) {
          buttonState = state;
      }
      
      lastButtonState = state;
      return buttonState;
  }
  
private:
  int buttonState = 0;
  int lastButtonState = 0;
  long lastDebounceTime = 0;
  long debounceDelay = 250;
};

void setup(){
  Serial.begin(SerialRate);
  pinMode(BuzzerPortOut, OUTPUT);
}

TButton<ButtonPin4> Button4;
TButton<ButtonPin5> Button5;

void loop(){
  
  if(Button4.state()){
    stateB = 1;
  }else{
    stateB = 0;
  }
  if(Button5.state()){
    stateD = 1;
  }else{
    stateD = 0;
  }

  Serial.print("Beep-test:");
  Serial.print(stateB);
  Serial.print(stateD);
  Serial.print("\n");
  
  if(stateB+stateD == 2){
    digitalWrite(BuzzerPortOut, HIGH);
    delay(100);
  }
  digitalWrite(BuzzerPortOut, LOW);
  
  
  //Serial.print(digitalRead(ButtonPin4));
}
