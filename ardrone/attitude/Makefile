all: clean attitude

setup:
	mkdir -p ../bin/attitude

attitude: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ ../util/util.c ../gpio/gpio.c ../navboard/navboard.c ars.c attitude.c main_attitude.c
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -o ../bin/attitude/attitude ../util/util.c ../gpio/gpio.c ../navboard/navboard.c ars.c attitude.c main_attitude.c

clean:
	rm -rf ../bin/attitude