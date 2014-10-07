all: setup original allOn forward left back right hover m1 m2 m3 m4

setup:
	mkdir -p ../bin/motorboard/

original: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard.c
	rm -f ../bin/motorboard/motorboard_original
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard/motorboard_original motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard.c

allOn: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_allOn.c
	rm -f ../bin/motorboard/motorboard_allOn
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard/motorboard_allOn motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_allOn.c

forward: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallForward.c
	rm -f ../bin/motorboard/motorboard_forward
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard/motorboard_forward motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallForward.c

left: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallLeft.c
	rm -f ../bin/motorboard/motorboard_left
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard/motorboard_left motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallLeft.c

back: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallBack.c
	rm -f ../bin/motorboard/motorboard_back
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard/motorboard_back motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallBack.c

right: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallRight.c
	rm -f ../bin/motorboard/motorboard_right
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard/motorboard_right motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallRight.c

hover: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_hover.c
	rm -f ../bin/motorboard/motorboard_right
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard/motorboard_hover motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_hover.c

m1: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m1.c
	rm -f ../bin/motorboard/motorboard_right
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard/motorboard_motor1 motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m1.c

m2: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m2.c
	rm -f ../bin/motorboard/motorboard_right
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard/motorboard_motor2 motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m2.c

m3: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m3.c
	rm -f ../bin/motorboard/motorboard_right
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard/motorboard_motor3 motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m3.c

m4: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m4.c
	rm -f ../bin/motorboard/motorboard_right
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard/motorboard_motor4 motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_m4.c

clean:
	rm -rf ../bin/motorboard