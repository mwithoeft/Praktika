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

#ifdef __cplusplus
extern "C" {

void _init(void) {
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
//Delay
const uint8_t Task1Delay = 2000;
const uint8_t Task2Delay = 1000;
//Ports
const uint8_t readLight = PD_1;
const uint8_t readTemp = PD_0;
const uint8_t heating = PC_4;
//Values
const int MaxTemp = 600;
const int MinTemp = 300
const int LightValue = 200;
//states
const int Kuehlen = 0;
const int Heizen = 1;
const int Aus = 2;
uint16_t read;
int state = Kuehlen;
int history;
void loop() {

}

void setup() {
  // initialize the digital pin as an output.
  pinMode(PC_4, OUTPUT);
  pinMode(PD_0, INPUT);
  pinMode(PD_1, INPUT);
  Serial.begin(9600);
}

void tempTask(void *pvParameters) {
	for(;;){
		Serial.print("\nTemperatur Task:\n");
		read = analogRead(readTemp);
		Serial.print("Temperatur:");
		Serial.print(read);
		Serial.print("\n");
		switch(state){
			case Kuehlen:
				if(read >= MinTemp){
					Serial.print("Kuehlen\n");
				}else{
					Serial.print("Heizung wird angemacht\n");
					state = Heizen;
					digitalWrite(heating, HIGH);
				}
				break;
			case Heizen:
				if(read <= MaxTemp){
					Serial.print("Heizen\n");
				}else{
					Serial.print("Heizung wird ausgemacht\n");
					state = Kuehlen;
					digitalWrite(heating, LOW);
				}
				break;
		}
		vTaskDelay(Task2Delay);
	}
	history = state;
}
void lightTask(void *pvParameters) {
	for(;;){
	    Serial.print("\nlight task\n");
		read = analogRead(readLight);
		Serial.print("light:");
		Serial.print(read);
		Serial.print("\n");
		switch(state){
			case Aus:
				if(read < LightValue){
					Serial.print("Es ist dunkel die Heizung wird angemacht\n");
					state = history;
				}else{
					Serial.print("Es ist zu hell zum heizen\n");
				}
				break;
			case Kuehlen:
			case Heizen:
				if(read >= LightValue){
					state = Aus;
					Serial.print("Es ist hell die Heizung wird ausgemacht\n");
					digitalWrite(heating, LOW);
				}else{
					Serial.print("Es ist dunkel und wird geheizt\n");
				}
				break;
		}
	vTaskDelay(Task1Delay);
	}
}

int main(void) {
	setup();

	xTaskCreate(lightTask, "TASK 1", configMINIMAL_STACK_SIZE + 100, NULL,
			tskIDLE_PRIORITY + 2UL, NULL);

	xTaskCreate(tempTask, "TASK 2", configMINIMAL_STACK_SIZE + 100, NULL,
			tskIDLE_PRIORITY + 1UL, NULL);
	vTaskStartScheduler();
}
