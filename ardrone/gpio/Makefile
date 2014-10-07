all: clean gpio

setup:
	mkdir -p ../bin/gpio

gpio: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ ../util/util.c gpio.c main_gpio.c
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -o ../bin/gpio/gpio ../util/util.c gpio.c main_gpio.c

clean:
	rm -rf ../bin/gpio