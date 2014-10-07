all: clean fly

setup:
	mkdir -p ../bin/fly

fly: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ ../udp/udp.c ../util/util.c ../gpio/gpio.c ../motorboard/mot.c ../motorboard/motorboard.c ../navboard/navboard.c ../attitude/ars.c ../attitude/attitude.c pid.c controlthread.c main_fly.c
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/fly/fly ../udp/udp.c ../util/util.c ../gpio/gpio.c ../motorboard/mot.c ../motorboard/motorboard.c ../navboard/navboard.c ../attitude/ars.c ../attitude/attitude.c pid.c controlthread.c main_fly.c

clean:
	rm -rf ../bin/fly