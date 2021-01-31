CC=arm-none-eabi-gcc
MACH=cortex-m7
CFLAGS= -c -mcpu=$(MACH) -mthumb -Wall -std=gnu11 -O0 
LDFLAGS=  -T stm32_ls.ld -nostdlib -Wl,-Map=final.map
OC=arm-none-eabi-objcopy 
OCFLAG= -O ihex 
all: main.o stm32_startup.o final.elf final.hex

main.o:main.c 
	$(CC) $(CFLAGS) -o $@ $^
stm32_startup.o:stm32_startup.c 
	$(CC) $(CFLAGS) -o $@ $^
final.elf: main.o stm32_startup.o
	$(CC) $(LDFLAGS) -o $@ $^ 
final.hex:final.elf
	$(OC) $(OCFLAG) $^ $@
clean:
	rm -rf *.o *.elf *.map *.hex

load:
	openocd -f board/st_nucleo_f7.cfg
	
