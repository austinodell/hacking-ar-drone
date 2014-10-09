FILE = ../compiler_loc.dat
LOC = $(shell cat ${FILE})

all: clean fly

setup:
	mkdir -p ../bin/fly

fly: setup ../udp/udp.c ../util/util.c ../gpio/gpio.c ../motorboard/mot.c ../motorboard/motorboard.c ../navboard/navboard.c ../attitude/ars.c ../attitude/attitude.c pid.c controlthread.c main_fly.c
	$(LOC) -lpthread -o ../bin/fly/fly ../udp/udp.c ../util/util.c ../gpio/gpio.c ../motorboard/mot.c ../motorboard/motorboard.c ../navboard/navboard.c ../attitude/ars.c ../attitude/attitude.c pid.c controlthread.c main_fly.c

clean:
	rm -rf ../bin/fly