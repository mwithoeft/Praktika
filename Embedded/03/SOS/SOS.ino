/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * LaunchPad with an LED
  
  This example code is in the public domain.
*/

// most launchpads have a red LED
#define LED RED_LED

//see pins_energia.h for more LED definitions
//#define LED GREEN_LED
//Break timers
#define LONGBREAK 2000
#define SHORTBREAK 500
  
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);     
}

void morseS(){
  for(int i = 0;i<3;i++){
    blink(SHORTBREAK);
  }
}

void morseO(){
  for(int i = 0;i<3;i++){
    blink(LONGBREAK);
  }
}

void blink(int pause){
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(pause);             // wait
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(SHORTBREAK);              // wait
}

// the loop routine runs over and over again forever:
void loop() {
  morseS();
  morseO();
  morseS();
  delay(LONGBREAK);
}
