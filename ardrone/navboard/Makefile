FILE = ../compiler_loc.dat
LOC = $(shell cat ${FILE})

all: clean navboard

setup:
	mkdir -p ../bin/navboard

navboard: setup ../util/util.c ../gpio/gpio.c navboard.c main_navboard.c
	$(LOC) -o ../bin/navboard/navboard ../util/util.c ../gpio/gpio.c navboard.c main_navboard.c

test: $(LOC) ../util/util.c ../gpio/gpio.c navboard.c main_navboard_test.c
	rm -f ./test_navboard
	$(LOC) -o test_navboard ../util/util.c ../gpio/gpio.c navboard.c main_navboard_test.c

clean:
	rm -rf ../bin/navboard