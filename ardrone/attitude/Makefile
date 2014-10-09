FILE = ../compiler_loc.dat
LOC = $(shell cat ${FILE})

all: clean attitude

setup:
	mkdir -p ../bin/attitude

attitude: setup ../util/util.c ../gpio/gpio.c ../navboard/navboard.c ars.c attitude.c main_attitude.c
	$(LOC) -o ../bin/attitude/attitude ../util/util.c ../gpio/gpio.c ../navboard/navboard.c ars.c attitude.c main_attitude.c

clean:
	rm -rf ../bin/attitude