// our working number
volatile uint8_t number = 1;

// baudrate for serial communication
const int baudRate = 9600;

// initialize Serial
void setup() {
  Serial.begin(baudRate);
}

// main loop
void loop() {
  // print number
  Serial.println(number);

  asm volatile(
    "CMP %[input], #128\n\t"
    "BEQ over127\n\t"
    "LSL %[result], #1 \n\t"
    "B.n end \n\t"
    "over127:\n\t"
    "mov %[result], #1\n\t"
    "end:\n\t"
   : [result] "+r" (number)               /* Output operand */
   : [input] "r" (number)                 /* Input operand */
  
  );
  delay(500);
}
