#include <Energia.h>

const byte buttonstate_released = 0;
const byte buttonstate_pressed = 1;
const byte buttonstate_held = 2;
const byte buttonstate_is_released = 3;

template <const uint8_t PIN_NB>
class TButton {
public:
  TButton(){}
  boolean state(){
    byte buttonValue = digitalRead(PIN_NB);

    if(buttonState == buttonstate_released && buttonValue == HIGH) {
        // Button is pressed
        buttonState = buttonstate_pressed;
        return HIGH;
    } else if (buttonState == buttonstate_pressed && buttonValue == HIGH) {
        // Button is held
        buttonState = buttonstate_held;
        return LOW;
    } else if (buttonState == buttonstate_held && buttonValue == LOW) {
        // Button is released
        buttonState = buttonstate_is_released;
        return LOW;
    } else if (buttonState == buttonstate_is_released && buttonValue == LOW) {
        // Button released
        buttonState = buttonstate_released;
        return LOW;
    }
    return LOW;
  }
private:
  byte buttonState = buttonstate_released;

};
