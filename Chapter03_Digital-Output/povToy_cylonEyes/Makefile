
##########------------------------------------------------------##########
##########              Project-specific Details                ##########
##########------------------------------------------------------##########
MCU   = atmega328p
F_CPU = 1000000UL
BAUD  = 19200UL

## A directory for common include files and the simple USART library.
LIBDIR = ../../AVR-Programming-Library

# these dirs arent used they are just a reminder to where these files are located
ARDUINO_CORE_DIR = C:/Program Files (x86)/Arduino/libraries
ARDUINO_LIB_DIR = C:/Users/lmerz/Documents/Arduino/libraries


##########------------------------------------------------------##########
##########                 Programmer Defaults                  ##########
##########------------------------------------------------------##########

PROGRAMMER_TYPE = avrisp
# extra arguments to avrdude: baud rate, chip type, -F flag, etc.
PROGRAMMER_ARGS = -P com8 -b 19200 -v

######
#####------------------------------------------------------##########
##########                  Program Locations                   ##########
##########------------------------------------------------------##########

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude


##########------------------------------------------------------##########
##########                   Makefile Directories               ##########
##########------------------------------------------------------##########

#The name of your project (without .c)
# TARGET = blinkLED or name it after enclosing directory
TARGET = $(lastword $(subst /, ,$(CURDIR)))

# find all c/cpp files in current directory and in LIBDIR variable
SOURCES=$(wildcard *.c $(LIBDIR)/*.c *.cpp)
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(SOURCES:.c=.h)


##########------------------------------------------------------##########
##########                   Makefile Settings                  ##########
##########------------------------------------------------------##########

## Compilation options, type man avr-gcc if you're curious.
CPPFLAGS = -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -I. -I$(LIBDIR)
CFLAGS = -Os -g -std=gnu99 -Wall
## Use short (8-bit) data types 
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums 
## Splits up object files per function
CFLAGS += -ffunction-sections -fdata-sections 
LDFLAGS = -Wl,-Map,$(TARGET).map 
## Optional, but often ends up with smaller code
LDFLAGS += -Wl,--gc-sections 
## Relax shrinks code even more, but makes disassembly messy
## LDFLAGS += -Wl,--relax
## LDFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm  ## for floating-point printf
## LDFLAGS += -Wl,-u,vfprintf -lprintf_min      ## for smaller printf
TARGET_ARCH = -mmcu=$(MCU)


##########------------------------------------------------------##########
##########  Explicit pattern rules: make .o files from .c files ##########
##########------------------------------------------------------##########

%.o: %.c $(HEADERS) Makefile
	 $(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@ $<;

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

%.hex: %.elf
	 $(OBJCOPY) -j .text -j .data -O ihex $< $@

%.eeprom: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ 

%.lst: %.elf
	$(OBJDUMP) -S $< > $@

## These targets don't have files named after them
.PHONY: all disassemble disasm eeprom size clean squeaky_clean flash fuses

all: $(TARGET).hex 

debug:
	@echo
	@echo "Source files:"   $(SOURCES)
	@echo "MCU, F_CPU, BAUD:"  $(MCU), $(F_CPU), $(BAUD)
	@echo	

# Optionally create listing file from .elf
# This creates approximate assembly-language equivalent of your code.
disassemble: $(TARGET).lst
disasm: disassemble

# Optionally show how big the resulting program is 
size:  $(TARGET).elf
	$(AVRSIZE) -C --mcu=$(MCU) $(TARGET).elf


##########------------------------------------------------------##########
##########              Clean out files from dir                ##########
##########------------------------------------------------------##########
clean:
	rm -f $(TARGET).elf $(TARGET).hex $(TARGET).obj \
	$(TARGET).o $(TARGET).d $(TARGET).eep $(TARGET).lst \
	$(TARGET).lss $(TARGET).sym $(TARGET).map $(TARGET)~ \
	$(TARGET).eeprom

squeaky_clean:
	rm -f *.elf *.hex *.obj *.o *.d *.eep *.lst *.lss *.sym *.map *~ *.eeprom


##########------------------------------------------------------##########
##########              Programmer-specific details             ##########
##########------------------------------------------------------##########

flash: $(TARGET).hex 
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U flash:w:$<

flash_eeprom: $(TARGET).eeprom
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U eeprom:w:$<

avrdude_terminal:
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -nt


##########------------------------------------------------------##########
##########                     Fuse Defaults                    ##########
##########------------------------------------------------------##########

## Mega 48, 88, 168, 328 default values
LFUSE = 0x62
HFUSE = 0xD9
EFUSE = 0x00

## Generic fuse setting
FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m 

fuses: 
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) \
	           $(PROGRAMMER_ARGS) $(FUSE_STRING)
show_fuses:
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -nv	


##########------------------------------------------------------##########
##########                     Fuse settings                    ##########
##########------------------------------------------------------##########

## Called with no extra definitions, sets to defaults
set_default_fuses:  FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m 
set_default_fuses:  fuses

## set arduino based fuses
set_arduino_fuses: LFUSE = 0xff
set_arduino_fuses: HFUSE = 0xde
set_arduino_fuses: EFUSE = 0x05
set_arduino_fuses: FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m
set_arduino_fuses: fuses

## Set the fuse byte for full-speed mode
## Note: can also be set in firmware for modern chips
set_fast_fuse: LFUSE = 0xE2
set_fast_fuse: FUSE_STRING = -U lfuse:w:$(LFUSE):m 
set_fast_fuse: fuses

## Set the EESAVE fuse byte to preserve EEPROM across flashes
set_eeprom_save_fuse: HFUSE = 0xD7
set_eeprom_save_fuse: FUSE_STRING = -U hfuse:w:$(HFUSE):m
set_eeprom_save_fuse: fuses

## Clear the EESAVE fuse byte
clear_eeprom_save_fuse: FUSE_STRING = -U hfuse:w:$(HFUSE):m
clear_eeprom_save_fuse: fuses
