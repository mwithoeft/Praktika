#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

volatile uint32_t ui32Loop;

void delay() {
    for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);
}

int main(void) {
    // Enable the GPIO port.
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    // Do a dummy read to insert a few cycles
    ui32Loop = SYSCTL_RCGC2_R;

    // Set up GPIO port.
    GPIO_PORTF_DIR_R = 0x08;
    GPIO_PORTF_DEN_R = 0x08;

    // Loop forever.
    while(1) {
        // Turn on the LED.
        GPIO_PORTF_DATA_R |= 0x08;

        // Delay for a bit.
        delay();

        // Turn off the LED.
        GPIO_PORTF_DATA_R &= ~(0x08);

        // Delay for a bit.
        delay();
    }
}
