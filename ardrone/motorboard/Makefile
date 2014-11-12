FILE = ../compiler_loc.dat
LOC = $(shell cat ${FILE})

all: clean original allOn forward left back right hover m1 m2 m3 m4 ledoff ledgreen socket

setup:
	mkdir -p ../bin/motorboard/

original: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard.c
	rm -f ../bin/motorboard/motorboard_original
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_original motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard.c

allOn: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_allOn.c
	rm -f ../bin/motorboard/motorboard_allOn
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_allOn motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_allOn.c

forward: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallForward.c
	rm -f ../bin/motorboard/motorboard_forward
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_forward motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallForward.c

left: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallLeft.c
	rm -f ../bin/motorboard/motorboard_left
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_left motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallLeft.c

back: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallBack.c
	rm -f ../bin/motorboard/motorboard_back
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_back motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallBack.c

right: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallRight.c
	rm -f ../bin/motorboard/motorboard_right
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_right motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallRight.c

hover: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_hover.c
	rm -f ../bin/motorboard/motorboard_hover
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_hover motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_hover.c

m1: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m1.c
	rm -f ../bin/motorboard/motorboard_motor1
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_motor1 motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m1.c

m2: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m2.c
	rm -f ../bin/motorboard/motorboard_motor2
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_motor2 motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m2.c

m3: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m3.c
	rm -f ../bin/motorboard/motorboard_motor3
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_motor3 motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m3.c

m4: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m4.c
	rm -f ../bin/motorboard/motorboard_motor4
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_motor4 motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m4.c

ledoff: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_leds_off.c
	rm -f ../bin/motorboard/motorboard_leds_off
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_leds_off motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_leds_off.c

ledgreen: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_leds_green.c
	rm -f ../bin/motorboard/motorboard_leds_off
	$(LOC) -lpthread -o ../bin/motorboard/motorboard_leds_green motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_leds_green.c

socket: setup motorboard.c mot.c ../gpio/gpio.c ../util/util.c motor_socket.c
	rm -f ../bin/motorboard/motor_socket
	$(LOC) -lpthread -o ../bin/motorboard/motor_socket motorboard.c mot.c ../vbat/vbat.c ../gpio/gpio.c ../util/util.c motor_socket.c

clean:
	rm -rf ../bin/motorboard

.PHONY: all