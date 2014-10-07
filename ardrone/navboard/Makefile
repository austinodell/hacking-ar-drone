FILE = ../compiler_loc.dat
LOC = $(shell cat ${FILE})

all: clean navboard

setup:
	mkdir -p ../bin/navboard

navboard: setup $(LOC) ../util/util.c ../gpio/gpio.c navboard.c main_navboard.c
	$(LOC) -o ../bin/navboard/navboard ../util/util.c ../gpio/gpio.c navboard.c main_navboard.c

clean:
	rm -rf ../bin/navboard