**Praktikum 4 – Energia: Polling und Interrupts            				Valentin Hertel Moritz Withöft**

 

**Aufgabe 1** *(2 Punkte)* 

*Implementieren Sie die fehlende Klasse* TButton *(Konstruktor und Funktion* state*).* 

Laden Sie das Programm auf das LaunchPad hoch und testen Sie es. (Tipp: Das Programm können Sie mit dem Knopf „Reset“ auf dem LaunchPad neustarten.) 

*Wie verhält sich ein Auslösen des “Not-Aus-Knopfs” hinsichtlich der Reaktionszeit?* 

*Dadurch, dass im loop mit einem if gefragt wird ob der Taster gedrückt wurde, muss man den Taster solange gedrückt halten, bis das Programm im loop in der If Bedingung ist. Durch den delay von 2 sec dauert ein loop durchlauf etwas mehr als 2 Sekunden* 



**Aufgabe 2** *(2 Punkte)* 

*Verbessern Sie das Programm hinsichtlich der Reaktionszeit, indem Sie Polling einsetzen.*



**Aufgabe 3** *(1 Punkt)* 

*Geben Sie mittels der Serial-Klasse Debug-Informationen vom LaunchPad an Ihr System aus, wenn der Not-Aus-Knopf betätigt wird.*

```c++
// Demo illustrating blinking led and reading of button.
// Led is finally turned off when button is pressed. 

// define port for led output
const uint8_t LedPortOut = RED_LED;
// define pin for button input
const uint8_t ButtonPinIn = PC_4;
// define delay for blinking in ms
const uint32_t Delay = 100;
const uint32_t Delay2 = 2000;


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


//....TODO: INSERT CODE FOR CLASS TBUTTON....
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

void polling(){
  for (int i = Delay2;i>Delay;i-=Delay){
    if (Button.state() == HIGH) {
        Serial.print("Notaus wurde betätigt\n");
        Led.off();
        delay(Delay2);
    }
    delay(Delay);
  }
}

void setup() {Serial.begin(9600);}
  
void loop() {
    polling();
    Led.toggle();
}
```



**Aufgabe 4** *(3 Punkte)* 

*Implementieren Sie nun die Not-Aus-Funktionalität mittels Nutzung der TivaWare-ROM-Funktionen zur Ausl*ö*sung eines Interrupts, d.h. ohne Energia-Funktion attachInterrupt() zu benutzen. Schreiben Sie hierzu ein neues Programm.* 

*(Siehe TivaWare*™ *Peripheral Driver Library. Dazu k*ö*nnten Ihnen auch Lab3 und Lab4 des LaunchPad-Workbooks helfen.)* 

```c++
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
```



**Aufgabe 5** *(2 Punkte)* 

*Schreiben Sie nun ein weiteres Programm, das die LED des LaunchPads über den Taster an- bzw. ausschaltet (toggeln). Stellen Sie dabei sicher, dass Ihre Implementierung der Klasse* TButton *eine Entprellung des Tasters vornimmt.*

```c++
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
//Serial frequency
const uint32_t serialFrequency = 9600;
//Buttonstate values
const byte buttonstate_released = 0;
const byte buttonstate_pressed = 1;
const byte buttonstate_held = 2;
const byte buttonstate_is_released = 3;

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
    byte buttonValue = digitalRead(PORT_BUTTON);

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
  }
private:
  byte buttonState = buttonstate_released;
};

// global instances for led output
TLed<LedPortOut> Led;
// and for button pin
TButton<ButtonPinIn> Button;

void setup() {
 Serial.begin(serialFrequency);
}

void loop() {
  //Toggle Button
  if (Button.state() == HIGH) {
    Led.toggle();
    Serial.print("Toggle\n");
}
}
```
