//LEDS
const uint8_t CarRedLED = PD_6;
const uint8_t CarYellowLED = PC_7;
const uint8_t CarGreenLED = PC_6;
const uint8_t PedastrianRedLED = PC_5;
const uint8_t PedastrianGreenLED = PC_4;

const uint8_t Pushbutton = PUSH2;

const int Tw = 5000;
const int Tu = 1000;
const int Tg = 5000;

int stateCounter = 1;

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
  long debounceDelay = 1000;
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
    void doBreak(){
      delay(pause);
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
  private:
  uint8_t fahrzeugLED1;
  uint8_t fahrzeugLED2 = NULL;
  uint8_t fussgaengerLED;
  int pause;
};

State state0 = State(CarGreenLED, PedastrianRedLED, 0);
State state1 = State(CarGreenLED, PedastrianRedLED, Tw);
State state2 = State(CarGreenLED, PedastrianRedLED, Tu);
State state3 = State(CarYellowLED, PedastrianRedLED, Tu);
State state4 = State(CarRedLED, PedastrianRedLED, Tu);
State state5 = State(CarRedLED, PedastrianGreenLED, Tg);
State state6 = state4;
State state7 = State(CarRedLED, CarYellowLED, PedastrianRedLED, Tu);

State state[] = {state0, state1, state2, state3, state4, state5, state6, state7};

void startSequenz(){
   State thisState = state[stateCounter];
   thisState.farhzeugAmpel();
   thisState.fussgaengerAmpel();
   thisState.doBreak();
   thisState.clear();
}
void setup(){
}
TButton<Pushbutton> push;
void loop(){ 
  state0.farhzeugAmpel();
  state0.fussgaengerAmpel();
  if(push.state()){
    while(true){
      if(stateCounter > 7){
        stateCounter = 2;
      }
      startSequenz();
      stateCounter++;
    }
  }
}
