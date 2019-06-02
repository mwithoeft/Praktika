#include <Energia.h>


#if defined(PART_TM4C129XNCZAD)
#include "inc/tm4c129xnczad.h"
#elif defined(PART_TM4C1294NCPDT)
#include "inc/tm4c1294ncpdt.h"
#elif defined(PART_TM4C1233H6PM) || defined(PART_LM4F120H5QR)
#include "inc/tm4c123gh6pm.h"
#else
#error "**** No PART defined or unsupported PART ****"
#endif

#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/eeprom.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
//My classes
#include "OutputStrategy.h"
#include "BuzzerOutput.cpp"
#include "LedOutput.cpp"
#include "Morse.cpp"
#include "TButton.cpp"

#ifdef __cplusplus
extern "C" {

void _init(void) {
	//delay(200);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
	if (ROM_EEPROMInit() == EEPROM_INIT_ERROR) {
		if (ROM_EEPROMInit() != EEPROM_INIT_ERROR)
			EEPROMMassErase();
	}

	timerInit();

	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
#ifdef TARGET_IS_SNOWFLAKE_RA0
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOR);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOS);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOT);
#endif

	//Unlock and commit NMI pins PD7 and PF0
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x4C4F434B;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x1;
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0x4C4F434B;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;

	// Deep Sleep mode init
	// DSLP clock = PIOSC / 16 = 1MHz
	// Note: Couldn't find the define constants for SysCtlDeepSleepPowerSet in the driverlib.
	//
#ifdef TARGET_IS_BLIZZARD_RB1
	ROM_SysCtlDeepSleepClockSet(SYSCTL_DSLP_DIV_16 | SYSCTL_DSLP_OSC_INT);
	SysCtlDeepSleepPowerSet(0x21); // FLASHPM = LOW_POWER_MODE, SRAMPM = STANDBY_MODE
	SysCtlLDODeepSleepSet(SYSCTL_LDO_1_00V); // Going lower tends to be very flaky and cause continual resets
	// particularly when measuring MCU current.
#endif
	//
#ifdef TARGET_IS_SNOWFLAKE_RA0
	ROM_SysCtlDeepSleepClockConfigSet(16, SYSCTL_DSLP_OSC_INT);
	SysCtlDeepSleepPowerSet(0x121); // TSPD, FLASHPM = LOW_POWER_MODE, SRAMPM = STANDBY_MODE
#endif
	//
} /* void _init(void) */

} /* extern "C" */
#endif
const uint8_t ledPortOut = RED_LED;
const uint8_t buzzerPortOut = PC_6;
const uint8_t ButtonPin4 = PC_4;
const uint8_t ButtonPin5 = PC_5;
Morse morse;
OutputStrategy out = BuzzerOutput(BuzzerPortOut);
bool mode = true;
void toggelOutput(){

    if(mode){
      Serial.print("Mode is LED\n");
      out = LedOutput(LedPortOut);
      mode = !mode;
   }else{
      Serial.print("Mode is Buzzer\n");
      out = BuzzerOutput(BuzzerPortOut);
      mode = !mode;

  }
  delay(1500);
  loop();
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
char inData[129]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte charIndex = 0; // Index into array; where to store the character
TButton<ButtonPin5> Button;
void loop() {
	while(Serial.available() != 0) // Don't read unless
	  // there you know there is data
	{
	  if(charIndex < 128) // One less than the size of the array
	  {
	    inChar = Serial.read(); // Read a character
	    inData[charIndex] = inChar; // Store it
	    charIndex++; // Increment where to write next
	    inData[charIndex] = '\0'; // Null terminate the string
	  }
	}
	morse.morseString(out, inData);
	 /*while(Button.state() == LOW){
		    while(Serial.available() == 0){}
		    char input = Serial.readString();

		    morse.morseString(out, str);

		  }*/
}

void setup() {
  Serial.begin(9600);
  interruptPin4();
}

void defaultTask(void *pvParameters) {
	for (;;) {
		loop();
		if (serialEventRun)
			serialEventRun();
	}
}

int main(void) {
	setup();

	xTaskCreate(defaultTask, "TASK 1", configMINIMAL_STACK_SIZE + 100, NULL,
			tskIDLE_PRIORITY + 1UL, NULL);
	vTaskStartScheduler();
}
