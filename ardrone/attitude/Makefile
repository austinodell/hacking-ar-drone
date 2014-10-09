FILE = ../compiler_loc.dat
LOC = $(shell cat ${FILE})

all: clean attitude

setup:
	mkdir -p ../bin/attitude

old: setup ../util/util.c ../gpio/gpio.c ../navboard/navboard.c ars.c attitude.c main_attitude.c
	$(LOC) -o ../bin/attitude/attitude ../util/util.c ../gpio/gpio.c ../navboard/navboard.c ars.c attitude.c main_attitude.c

clean:
	rm -rf ../bin/attitude

attitude: setup DroneKalman.cpp main_attitude.c moving_average.c ../util/util.c ../gpio/gpio.c ars.c ../navboard/navboard.c ../lowpass/lowpass.c
	$(LOC) -o ../bin/attitude/attitude DroneKalman.cpp main_attitude.c moving_average.c ../util/util.c ../gpio/gpio.c ars.c ../navboard/navboard.c ../lowpass/lowpass.c