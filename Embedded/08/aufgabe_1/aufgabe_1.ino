//LEDS
const uint8_t CarRedLED = PD_6;
const uint8_t CarYellowLED = PC_7;
const uint8_t CarGreenLED = PC_6;
const uint8_t PedastrianRedLED = PC_5;
const uint8_t PedastrianGreenLED = PC_4;

const uint8_t Button = PUSH2;

const uint8_t Tw;
const uint8_t Tu = 1000;
const uint8_t Tg;

void setup(){
  pinMode(CarRedLED, OUTPUT);
  pinMode(CarYellowLED, OUTPUT);
  pinMode(CarGreenLED, OUTPUT);
  pinMode(PedastrianRedLED, OUTPUT);
  pinMode(PedastrianGreenLED, OUTPUT);

  digitalWrite(CarGreenLED, HIGH);
  digitalWrite(PedastianRedLED, HIGH);
}

void switchLED(const uint8_t led1, const uint8_t led2){
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  
}

void greenToRed(){
  switchLED(CarGreenLED, CarYellowLED);
  delay(Tu);
  switchLED(CarYellowLED, CarRedLED);
  delay(TU);
  switchLED(PedastrianRedLED, PedastrianGreenLED);
}

void redToGreen(){
  
}

void startSequenz(){
  greenToRed();
  delay(Tg);
  redToGreen();
  
}


void loop(){

  if(digitalRead(Button){
    delay(Tw);
    startSequenz();
    
    
  }
  
}
