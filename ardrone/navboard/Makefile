all: clean navboard

setup:
	mkdir -p ../bin/navboard

navboard: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ ../util/util.c ../gpio/gpio.c navboard.c main_navboard.c
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -o ../bin/navboard/navboard ../util/util.c ../gpio/gpio.c navboard.c main_navboard.c

clean:
	rm -rf ../bin/navboard