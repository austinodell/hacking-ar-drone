FILE = ../compiler_loc.dat
LOC = $(shell cat ${FILE})

all: clean gpio

setup:
	mkdir -p ../bin/gpio

gpio: setup $(LOC) ../util/util.c gpio.c main_gpio.c
	$(LOC) -o ../bin/gpio/gpio ../util/util.c gpio.c main_gpio.c

clean:
	rm -rf ../bin/gpio