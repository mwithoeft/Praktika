
#include "inc/tm4c123gh6pm.h" // Definitions for the interrupt and register assignments on the Tiva C Series device on the LaunchPad board
#include "driverlib/interrupt.h" // Defines and macros for NVIC Controller (Interrupt) API of driverLib. This includes API functions such as IntEnable and IntPrioritySet.

// Demo illustrating blinking led and reading of button.
// Led is finally turned off when button is pressed.

// define port for led output
const uint8_t LedPortOut = RED_LED;
// define pin for button input
const uint8_t ButtonPinIn = PC_4;
// define delay for blinking in ms
const uint32_t Delay = 2000;

//! LED handling class. Has disable() function for emergency stop.
//! Parameter (in): PORT_NB (output port for connected led)
template <const uint8_t PORT_NB>
class TLed {
  public:
    //! Constructor takes state (HIGH, LOW) only if given.
    //! Defaults: value for state = LOW, and is not disabled.
    TLed(const uint8_t f_ledState = LOW)
      : m_ledState(f_ledState), m_disabled(false) {
      pinMode(PORT_NB, OUTPUT); // led is always output
      digitalWrite(PORT_NB, m_ledState); // set led to default state
    }
    //! If this led is disable, nothing happens, otherwise
    //! toggles state of led (from HIGH to LOW or from LOW to HIGH).
    void toggle() {
      if (m_disabled) // somehow no longer active
        return;
      if (m_ledState == LOW) { // toggle state
        m_ledState = HIGH;
      }
      else {
        m_ledState = LOW;
      }
      digitalWrite(PORT_NB, m_ledState); // set led to current state
    }
    //! Turn led finally off (emergency stop), state is set LOW, functionality off.
    void off() {
      m_disabled = true;
      m_ledState = LOW;
      digitalWrite(PORT_NB, m_ledState); // set led to current state
    }
  private:
    uint8_t m_ledState; // current state of led
    bool m_disabled; // disable flag (on if led is finally turned off)
};

//! Button handling class. Has state() function for checking signal.
//! Parameter: ButtonPinIn (input port for connected button)
template <const uint8_t PORT_BUTTON>
class TButton {
public:
  TButton(){
    pinMode(PORT_BUTTON, INPUT);
  }
  boolean state(){
    return digitalRead(PORT_BUTTON);
    //return false;
  }
private:
};

// global instances for led output
TLed<LedPortOut> Led;
// and for button pin
TButton<ButtonPinIn> Button;

void buttonHandler(){
  Led.off();
}

void setup() {
  // Set data rate (baud) for serial data transmission
  // Setup input pin (Port C, Pin 4)
  GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);
  // Disable and clear interrupts for the input pin
  GPIOIntDisable(GPIO_PORTC_BASE, GPIO_PIN_4);
  GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_4);
  // Register handler function and trigger condition
  GPIOIntRegister(GPIO_PORTC_BASE, buttonHandler);
  GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_RISING_EDGE);
  // Enable interrupts again
  GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4);
}

void loop() {
  //Toggle LED
  Led.toggle();
  //Delay
  delay(Delay);
}
