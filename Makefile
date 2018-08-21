EXE=74test
CC=avr-gcc
SRCS=$(shell echo *.c)
OBJS=$(SRCS:%.c=%.o)
OBJCOPY=avr-objcopy -O ihex -R .eeprom
LDFLAGS=-mmcu=atmega2560
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega2560
RM=rm
AVRDUDE=avrdude -F -V -c stk500v2 -p m2560 -P
SERIAL_DEV=/dev/ttyACM0
BAUDRATE=115200

ALL all: $(EXE) $(EXE).hex

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o

$(EXE) $(EXE).hex: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXE)
	$(OBJCOPY) $(EXE) $(EXE).hex

upload: $(EXE).hex
	$(AVRDUDE) $(SERIAL_DEV) -b $(BAUDRATE) -U flash:w:$(EXE).hex:i

clean:
	$(RM) $(OBJS) $(EXE) $(EXE).hex

.PHONY:clean $(EXE) upload ALL

