// Demo illustrating blinking led and reading of button.
// Led is finally turned off when button is pressed.
#include "driverlib/interrupt.h"
// define port for led output
const uint8_t LedPortOut = RED_LED;
// define pin for button input
const uint8_t ButtonPinIn = PC_4;
// define delay for blinking in ms
const uint32_t Delay = 2000;

uint8_t m_ledState = LOW; // current state of led
bool m_disabled = false; // disable flag (on if led is finally turned off)

void toggle() {
      if (m_disabled) // somehow no longer active
        return;
      if (m_ledState == LOW) { // toggle state
        m_ledState = HIGH;
      }
      else {
        m_ledState = LOW;
      }
      digitalWrite(LedPortOut, m_ledState); // set led to current state
}
void off() {
  m_disabled = true;
  m_ledState = LOW;
  digitalWrite(LedPortOut, m_ledState); // set led to current state
}

void setup() {
  pinMode(LedPortOut, OUTPUT); // led is always output
  IntRegister(ButtonPinIn, &off);
  IntEnable(ButtonPinIn);
  IntMasterEnable();
}
void loop() {
  toggle();
  // wait
  delay(Delay);
}
