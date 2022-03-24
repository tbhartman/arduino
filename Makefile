include Makefile.arduinoConfig

.PHONY: build test echo

test: test.exe

Makefile.arduinoConfig:
	+arduino-cli config dump | grep "user:" | sed "s/  user: /ARDUINO_USER = /"  | sed "s/\\\\\\\\/\\\\//g" > $@

ARDUINO_INCLUDES=$(ARDUINO_USER)/libraries
U8G2_CLIB=$(ARDUINO_INCLUDES)/U8g2/src/clib
INCLUDES=-Iutil -I$(ARDUINO_INCLUDES)/U8g2/src

echo::
	echo -E '$(ARDUINO_INCLUDES)'

build: build/arduino.samd.nano_33_iot/Blink.ino.elf

util/Fonts.txt: $(U8G2_CLIB)/u8g2.h
	grep -o "uint8_t u8g2_font\w*" $^ | sed 's/uint8_t //'> $@

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $< -o $@

build/arduino.samd.nano_33_iot/*.ino.elf: *.ino
	arduino-cli compile --fqbn arduino:samd:nano_33_iot --export-binaries --discovery-timeout=0s $^

CFLAGS = -g -Wall -I$(U8G2_CLIB)

U8SRC = $(shell ls $(U8G2_CLIB)/*.c)
U8OBJ = $(U8SRC:.c=.o)
UTILH = $(shell ls util/*.h)
UTILSRC = $(shell ls util/*.cpp)
UTILOBJ = $(UTILSRC:.cpp=.o)

CC = clang
CPP = clang++

CFLAGS = -DSPNG_USE_MINIZ

u8x8.a: $(U8OBJ)
	llvm-ar cr $@ $^

util.a: $(UTILOBJ) $(UTILH)
	llvm-ar cr $@ $(UTILOBJ)

TESTDEPS = blinker.o test.main.o u8x8.a util.a

test.exe: $(TESTDEPS)
	$(CPP) $(CFLAGS) $(LDFLAGS) $(TESTDEPS) -o $@

clean:
	rm -f $(TESTDEPS) $(UTILOBJ) test.exe
