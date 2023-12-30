# Makefile
DESTINATION  = firmware
DEVICE       = atmega328p
PROGRAMMER   = arduino
AVRDUDE      = avrdude -v -V  -p $(DEVICE) -c $(PROGRAMMER) -P /dev/ttyUSB0 -b 115200

default: build

build: clean
	@mkdir target
	@avr-gcc -mmcu=$(DEVICE) -Os -Wall -c ./src/drivers/gpio.c -o ./target/gpio.o
	@avr-gcc -mmcu=$(DEVICE) -Os -Wall -c ./src/drivers/motors.c -o ./target/motors.o
	@avr-gcc -mmcu=$(DEVICE) -Os -Wall -c ./src/main.c -o ./target/main.o
	@avr-gcc -mmcu=$(DEVICE) -Os -Wall -o ./target/$(DESTINATION).elf ./target/main.o ./target/motors.o ./target/gpio.o
	@avr-objcopy --input-target elf32-avr --output-target ihex --verbose ./target/$(DESTINATION).elf ./target/$(DESTINATION).hex
	@echo "INFO: build finished"

clean:
	@rm --force --recursive --verbose ./target
	@echo "INFO: clean finished"

disasm: ./target/$(DESTINATION).elf
	@avr-objdump -d ./target/$(DESTINATION).elf

size:	./target/$(DESTINATION).elf
	@avr-size --format=AVR --mcu=$(DEVICE) ./target/$(DESTINATION).elf 

check:
	@$(AVRDUDE)
	
upload:
	@$(AVRDUDE)  -D -U flash:w:./target/$(DESTINATION).hex:i
