#include "inc/tm4c123gh6pm.h" 
#include "driverlib/interrupt.h" 
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
//Serial data rate
const int SerialRate = 9600; 
//short
const uint16_t Dit = 500;
//long
const uint16_t Dah = Dit * 3;
//delay between wordds
const uint16_t WordDelay = Dit * 7;
const uint8_t LedPortOut = RED_LED;
const uint8_t BuzzerPortOut = PC_6;
const uint8_t ButtonPin4 = PC_4;
const uint8_t ButtonPin5 = PC_5;
String string = "";
bool mode = true;

const byte buttonstate_released = 0;
const byte buttonstate_pressed = 1;
const byte buttonstate_held = 2;
const byte buttonstate_is_released = 3;

 

// Strategy pettern
class OutputStrategy{
  public:
    OutputStrategy(const uint8_t pin)
      : outputPin(pin){
      pinMode(outputPin, OUTPUT);
    }
    void printMorse(char character){
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
        }else if(character == '_'){
          digitalWrite(outputPin, LOW);
          delay(Dit);
        }
    }
    OutputStrategy& operator=(const OutputStrategy& other){
      if(this != &other){
        this->outputPin = other.outputPin;
      }
      return *this;
    }
  protected:
  uint8_t outputPin;
};

class LedOutput : public OutputStrategy{
  public:
    LedOutput()
    :OutputStrategy(LedPortOut){}
};

class BuzzerOutput : public OutputStrategy{
  public:
    BuzzerOutput()
    :OutputStrategy(BuzzerPortOut){}
};

class Morse{
  public:
    String morseEncode(char x) { 
     switch (x) { 
      case 'a': 
        return ".-"; 
      case 'b': 
        return "-..."; 
      case 'c': 
        return "-.-."; 
      case 'd': 
        return "-.."; 
      case 'e': 
        return "."; 
      case 'f': 
        return "..-."; 
      case 'g': 
        return "--."; 
      case 'h': 
        return "...."; 
      case 'i': 
        return ".."; 
      case 'j': 
        return ".---"; 
      case 'k': 
        return "-.-"; 
      case 'l': 
        return ".-.."; 
      case 'm': 
        return "--"; 
      case 'n': 
        return "-."; 
      case 'o': 
        return "---"; 
      case 'p': 
        return ".--."; 
      case 'q': 
        return "--.-"; 
      case 'r': 
        return ".-."; 
      case 's': 
        return "..."; 
      case 't': 
        return "-"; 
      case 'u': 
        return "..-"; 
      case 'v': 
        return "...-"; 
      case 'w': 
        return ".--"; 
      case 'x': 
        return "-..-"; 
      case 'y': 
        return "-.--"; 
      case 'z': 
        return "--.."; 
      case '0': 
        return "-----";
      case '1': 
        return ".----";
      case '2': 
        return "..---";
      case '3': 
        return "...--";
      case '4': 
        return "....-";
      case '5': 
        return ".....";
      case '6': 
        return "-....";
      case '7': 
        return "--...";
      case '8': 
        return "---..";
      case '9': 
        return "----.";
      case ' ': 
        return "_______";
    } 
   }
    void morseString(OutputStrategy out, String input){
      String morsecode ="";
      for(int i = 0; i < input.length()-1; i++){
        Serial.print("Buchstabe:");
        Serial.print(input.charAt(i));
        Serial.print(morseEncode(input.charAt(i)));
         Serial.print("\n");
         morsecode += morseEncode(input.charAt(i)); 
         //Delay between two charakters
         morsecode += "_";
        } 
      for(int i = 0; i < morsecode.length(); i++){
        out.printMorse(morsecode.charAt(i));
      }
    }
  private:
};
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
OutputStrategy out = BuzzerOutput();
TButton<ButtonPin5> Button;
Morse morse;

void toggelOutput(){
    if(mode){
      Serial.print("Mode is LED\n");
      out = LedOutput();
      mode = !mode;
   }else{
      Serial.print("Mode is Buzzer\n");
      out = BuzzerOutput();
      mode = !mode;
    
  }
  delay(1500);
  setup();
}
void doMorse(){
  Serial.print("Morse\n");
  if(string.length()>0){
    morse.morseString(out, string);  
  }
  Serial.print("end morse\n");
}
void interruptPin4(){
  //SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  //SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  //TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
  // Setup input pin (Port C, Pin 4)
  GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);

  // Disable and clear interrupts for the input pin
  GPIOIntDisable(GPIO_PORTC_BASE, GPIO_PIN_4);
  GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_4);
  // Register handler function and trigger condition
  GPIOIntRegister(GPIO_PORTC_BASE, toggelOutput);
  GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_RISING_EDGE);
  // Enable interrupts again
  GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4);
}
void interruptPin5(){
  //SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  //SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  //TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
  // Setup input pin (Port C, Pin 4)
  GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_5);

  // Disable and clear interrupts for the input pin
  GPIOIntDisable(GPIO_PORTC_BASE, GPIO_PIN_5);
  GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_5);
  // Register handler function and trigger condition
  GPIOIntRegister(GPIO_PORTC_BASE, doMorse);
  GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_RISING_EDGE);
  // Enable interrupts again
  GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_5);
}
void setup(){
  Serial.begin(SerialRate);
  interruptPin4();
}
void loop(){    
    if(digitalRead(PC_5)){
      doMorse();
   }
}
void serialEvent() {
  while (Serial.available()) {
    string += Serial.readString(); 
    string.toLowerCase();
    if (string.length() > 128){
      Serial.print("Eingabe Text ist zu lang geben Sie einen neuen ein");
      string = "";
    }
  }
}
