// our working data
const uint8_t lastFiboIndex = 13;
uint8_t fibData[lastFiboIndex];
const int waitTime = 1000;
// baudrate for serial communication
const int baudRate = 9600;
void setup() {
  // initialize Serial
  Serial.begin(baudRate);
  // init first two Fibonacci numbers
  fibData[0] = 1;
  fibData[1] = 1;
  asm volatile(
    "Mov r4, %[i]\n\t"
    "sub r4, #2\n\t"
    "Mov r5, %[arr]\n\t"
    
    "fibDataLoop: \n\t"
    "ldr r6, [r5, #0]\n\t"
    "ldr r7, [r5, #1]\n\t"
    "ADD r6, r7\n\t"
    
    "STR r6, [r5,#2]\n\t"
    "ADD r5, #1\n\t"
    
    "SUB r4, #1\n\t"
    "cmp r4, #0 \n\t"
    "Bne fibDataLoop\n\t"
    :
    : [arr] "r" (fibData), [i] "r" (lastFiboIndex)
    : "r4", "r5", "r6", "r7"
    );
}
// main loop
void loop() {
  // print data
  for (int i = 0; i < lastFiboIndex; i++)
  {
  Serial.println(fibData[i]);
  }
// delay 1s
delay(waitTime);
}
