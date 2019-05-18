arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O2 -IC:\Users\Valentin\AppData\Local\Energia15\packages\energia\hardware\tivac\1.0.3\system -std=gnu11 -c -o blink.o blink.c
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O2 -IC:\Users\Valentin\AppData\Local\Energia15\packages\energia\hardware\tivac\1.0.3\system -std=gnu11 -c -o startup_gcc.o startup_gcc.c
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O2 -T blink.ld -Xlinker --gc-sections -o blink.elf blink.o startup_gcc.o
arm-none-eabi-size blink.elf
arm-none-eabi-objdump -h -S blink.elf > blink0.asm
pause