CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
SIZE=avr-size
AVRDUDE=avrdude
REMOVE=rm -f

MCU=atmega328p

HEXFORMAT=ihex

AVRDUDE_MCU=m328p
AVRDUDE_PROGRAMMERID=usbasp
AVRDUDE_PORT=usb


AVRDUDE_LFUSE=E2
AVRDUDE_HFUSE=D9
AVRDUDE_EFUSE=FF

PROJECT=adc
F_CPU=8000000UL

OPTLEVEL=s

DEFINES=-DF_CPU=$(F_CPU)
INC=
LIBS=

CFLAGS=-I. $(INC) $(DEFINES) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall -Wstrict-prototypes               \
	-Wa,-ahlms=$(firstword                  \
	$(filter %.lst, $(<:.c=.lst)))

CPPFLAGS=-fno-exceptions \
	-Wa,-ahlms=$(firstword         \
	$(filter %.lst, $(<:.cpp=.lst))\
	$(filter %.lst, $(<:.cc=.lst)) \
	$(filter %.lst, $(<:.C=.lst)))

ASMFLAGS =-I. $(INC) -mmcu=$(MCU)        \
	-x assembler-with-cpp            \
	-Wa,-gstabs,-ahlms=$(firstword   \
	$(<:.S=.lst) $(<.s=.lst))

LDFLAGS=-Wl,-Map,$(TARGET).map -mmcu=$(MCU) \
	-lm $(LIBS)


SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c, %, $(SOURCES))
BUILT_OBJECTS=$(wildcard *.o)

TARGET=$(PROJECT).out
DUMPTARGET=$(PROJECT).s

HEXROM=$(PROJECT).hex
HEXTARGET=$(HEXROM) $(PROJECT).eep

CPPFILES=$(wildcard *.cpp)
CCFILES=$(wildcard *.cc)
CFILES=$(wildcard *.c)
ASMFILES=$(wildcard *.S)

OBJDEPS=$(ASMFILES:.S=.o)	\
	$(CFILES:.c=.o)			\
	$(CCFILES:.cc=.o)		\
	$(CPPFILES:.cpp=.o)

LST=$(filter %.lst, $(OBJDEPS:.o=.lst))

.SUFFIXES : .c .cc .cpp .C .o .out .s .S \
	.hex .eep .h .hh .hpp

.PHONY: upload clean stats

all: $(TARGET)

disasm: $(DUMPTRG) stats

stats: $(TARGET)
	$(OBJDUMP) -h $(TARGET)
	$(SIZE) -C -d --mcu=$(MCU) $(TARGET)

hex: $(HEXTARGET)

$(DUMPTRG): $(TARGET)
	$(OBJDUMP) -S  $< > $@

$(TARGET): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJDEPS)

#### Generating assembly ####
# asm from C
%.s: %.c
	$(CC) -S $(CFLAGS) $< -o $@

# asm from (hand coded) asm
%.s: %.S
	$(CC) -S $(ASMFLAGS) $< > $@


# asm from C++
.cpp.s .cc.s .C.s :
	$(CC) -S $(CFLAGS) $(CPPFLAGS) $< -o $@

#### Generating object files ####
# object from C
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@


# object from C++ (.cc, .cpp, .C files)
.cc.o .cpp.o .C.o :
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# object from asm
.S.o :
	$(CC) $(ASMFLAGS) -c $< -o $@

.out.hex:
	$(OBJCOPY) -j .text                    \
		-j .data                       \
		-O $(HEXFORMAT) $< $@

.out.eep:
	$(OBJCOPY) -j .eeprom                  \
		--change-section-lma .eeprom=0 \
		-O $(HEXFORMAT) $< $@

clean:
	$(REMOVE) *.o *.elf *.hex *.eep *.lst *.s *.map *.out

linter:
	@echo "{" > .gcc-flags.json
	@echo "	\"execPath\": \"$(CC)\"," >> .gcc-flags.json
	@echo "	\"gccDefaultCFlags\": \"$(CFLAGS)\"," >> .gcc-flags.json
	@echo " \"gccDefaultCppFlags\": \"$(CPPFLAGS)\"," >> .gcc-flags.json
	@echo "	\"gccErrorLimit\": 15," >> .gcc-flags.json
	@echo " \"gccIncludePaths\": \".\"," >> .gcc-flags.json
	@echo "	\"gccSuppressWarnings\": false" >> .gcc-flags.json
	@echo "}" >> .gcc-flags.json

upload: hex
	avrdude -p$(AVRDUDE_MCU) -c$(AVRDUDE_PROGRAMMERID) -e -U flash:w:$(PROJECT).hex:a -U eeprom:w:$(PROJECT).eep:a -U lfuse:w:0x$(AVRDUDE_LFUSE):m -U hfuse:w:0x$(AVRDUDE_HFUSE):m -U efuse:w:0x$(AVRDUDE_EFUSE):m
