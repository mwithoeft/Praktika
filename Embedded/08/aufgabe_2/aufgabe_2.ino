#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/hibernate.h"
//LEDS
const uint8_t CarRedLED = PD_6;
const uint8_t CarYellowLED = PC_7;
const uint8_t CarGreenLED = PC_6;
const uint8_t PedastrianRedLED = PC_5;
const uint8_t PedastrianGreenLED = PC_4;
//Button
const uint8_t Pushbutton = PUSH2;
//Energie save time
const int Te = 5000;
//Button wait
const int Tw = 2000;
//LED toggle time
const int Tu = 1000;
//Pedastrian green time
const int Tg = 2000;

int stateCounter = 0;
int bcount = 0;
template <const uint8_t PIN_NB>
class TButton {
public:
  TButton(){
    
    pinMode(PIN_NB, INPUT);
    }
    uint8_t state() {
     
      // prepare the default return value
      int returnValue = LOW;
      // read the state of the switch into a local variable
      int reading = digitalRead(PIN_NB);
      // If the switch changed, due to noise or pressing:
      if (reading != lastButtonState) {
        // reset the debouncing timer
        lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {
        // if the button state has changed:
        if (reading != buttonState) {
          buttonState = reading;
          // only return HIGH if the new button state is HIGH (i.e. rising edge)
          if (buttonState == LOW) { //PUSH2 is unused HIGH
            returnValue = HIGH;
          }
        }
      }

      // save the reading. Next time through the loop, it'll be the lastButtonState:
      lastButtonState = reading;

      return returnValue;
    }
private:
  int buttonState;
  int lastButtonState;
  long lastDebounceTime;
  long debounceDelay;
};

class Timer
{
  public:
    static Timer& instance() {
      static Timer timer;
      return timer;
    }
    void setFunction(void (*function)(void)) {
      TimerIntRegister(TIMER0_BASE, TIMER_A, function);
    }
    void setTimer(int timespan_ms) {
      float hz = 1 / (timespan_ms / 1000.0f);
      uint32_t ui32Span = (SysCtlClockGet() / hz);
      //Zeit setzten
      TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Span);

      //Timer und Interupt
      TimerEnable(TIMER0_BASE, TIMER_A);
      IntEnable(INT_TIMER0A);
      TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    }
    void resetTimer() {
      TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    }
  private:
    Timer() {
      SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
      TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);
    }
    // Blockt Copy-Konstruktor
    Timer( const Timer& );
    //Blockt Copy
    Timer & operator = (const Timer &);
};
class State {
  public:
    State(const uint8_t fahrzeugLED, const uint8_t fussgaengerLED, int pause)
    :fahrzeugLED1(fahrzeugLED), fussgaengerLED(fussgaengerLED), pause(pause){
      pinMode(fahrzeugLED, OUTPUT);
      pinMode(fussgaengerLED, OUTPUT);
    }
    State(const uint8_t fahrzeugLED1, const uint8_t fahrzeugLED2, const uint8_t fussgaengerLED, int pause)
    :fahrzeugLED1(fahrzeugLED1), fahrzeugLED2(fahrzeugLED2), fussgaengerLED(fussgaengerLED), pause(pause){
      pinMode(fahrzeugLED1, OUTPUT);
      pinMode(fahrzeugLED2, OUTPUT);
      pinMode(fussgaengerLED, OUTPUT);
    }
    void farhzeugAmpel(){
      if(fahrzeugLED2 != NULL){
        digitalWrite(fahrzeugLED1, HIGH);
        digitalWrite(fahrzeugLED2, HIGH);
      }else{
         digitalWrite(fahrzeugLED1, HIGH);
      }
    }
    void fussgaengerAmpel(){
       digitalWrite(fussgaengerLED, HIGH);
    }
    void clear(){
      if(fahrzeugLED2 != NULL){
        digitalWrite(fahrzeugLED1, LOW);
        digitalWrite(fahrzeugLED2, LOW);
        digitalWrite(fussgaengerLED, LOW);
      }else{
         digitalWrite(fahrzeugLED1, LOW);
         digitalWrite(fussgaengerLED, LOW);
      }
    }
     State& operator=(const State& other){
      if(this != &other){
        this->fahrzeugLED1 = other.fahrzeugLED1;
        this->fahrzeugLED2 = other.fahrzeugLED2;
        this->fussgaengerLED = fussgaengerLED;
      }
      return *this;
    }
    int getBreak(){
      return pause;
    }
  private:
  uint8_t fahrzeugLED1;
  uint8_t fahrzeugLED2 = NULL;
  uint8_t fussgaengerLED;
  int pause;
};



// init states
State state0 = State(CarGreenLED, PedastrianRedLED, Te);
State state1 = State(CarGreenLED, PedastrianRedLED, Tw);
State state2 = State(CarYellowLED, PedastrianRedLED, Tu);
State state3 = State(CarRedLED, PedastrianRedLED, Tu);
State state4 = State(CarRedLED, PedastrianGreenLED, Tg);
State state5 = state3;
State state6 = State(CarRedLED, CarYellowLED, PedastrianRedLED, Tu);
State state[] = {state0, state1, state2, state3, state4, state5, state6};

void sleep (){
  digitalWrite(CarRedLED, LOW );
  digitalWrite(CarYellowLED, LOW );
  digitalWrite(CarGreenLED, LOW );
  digitalWrite(PedastrianRedLED, LOW );
  digitalWrite(PedastrianGreenLED, LOW );
  HibernateRequest();
  while (1)
  {
  }
}


void sequenz(){
   stateCounter++;
   Timer::instance().resetTimer();
   state[stateCounter-1].clear();
    if(stateCounter > 6){
        stateCounter = 0;
    }  
   State thisState = state[stateCounter];
   thisState.farhzeugAmpel();
   thisState.fussgaengerAmpel();
   if(stateCounter == 0){
      Timer::instance().setFunction(sleep);
      Timer::instance().setTimer(thisState.getBreak());
   }else{
      Timer::instance().setTimer(thisState.getBreak());
   }
}
void setup(){
  Serial.begin(9600);
  Serial.print("start\n");
  SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
  HibernateEnableExpClk(SysCtlClockGet());
  HibernateGPIORetentionEnable();
  HibernateWakeSet(HIBERNATE_WAKE_PIN);
  
  Timer::instance().setFunction(sleep);
  Timer::instance().setTimer(Te);

  state0.farhzeugAmpel();
  state0.fussgaengerAmpel();
 
}
TButton<Pushbutton> push;
void loop(){ 
  if(push.state() && stateCounter == 0){
    Timer::instance().resetTimer();
    Timer::instance().setFunction(sequenz);
    Timer::instance().setTimer(Tw);
  }
  
}
