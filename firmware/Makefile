DEVICE  = atmega328
DEVICE_DUDE  = m328
F_CPU   = 12000000	# Hz

FUSE_L  = 0xff
FUSE_H  = 0xd9

AVRDUDE = avrdude -c dragon_isp -B 10 -p $(DEVICE_DUDE) -e
OBJECTS = usbdrv/usbdrv.o usbdrv/usbdrvasm.o usbdrv/oddebug.o main.o
CFLAGS  = -Iusbdrv -I. -DDEBUG_LEVEL=0
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(F_CPU) $(CFLAGS) -mmcu=$(DEVICE)


help:
	@echo "This Makefile has no default rule. Use one of the following:"
	@echo "make clean ..... to delete objects and hex file"
	@echo "make flash ..... to flash the firmware"
	@echo "make fuse ...... to flash the fuses"
	@echo "make hex ....... to build main.hex"


clean:
	rm -f \
		main.hex \
		main.lst \
		/gcmain.obj \
		main.cof \
		main.list \
		main.map \
		main.eep.hex \
		main.elf \
		*.o \
		usbdrv/*.o \
		main.s \
		usbdrv/oddebug.s \
		usbdrv/usbdrv.s


flash: main.hex
	$(AVRDUDE) -U flash:w:main.hex:i


fuse:
	@[ "$(FUSE_H)" != "" -a "$(FUSE_L)" != "" ] || \
		{ echo "*** Edit Makefile and choose values for FUSE_L and FUSE_H!"; exit 1; }
	$(AVRDUDE) -U hfuse:w:$(FUSE_H):m -U lfuse:w:$(FUSE_L):m


hex: main.hex

main.hex: main.elf
	rm -f main.hex main.eep.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size main.hex

# The $(OBJECT) dependency is necessary to automagically compile
# the object files (*.o) using generic rules defined below.
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)


# Generic rule for compiling C files:
.c.o:
	echo $< $@
	$(COMPILE) -c $< -o $@

# Generic rule for assembling Assembler source files:
.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

