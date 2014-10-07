all: standard allOn forward left back right

standard: /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard.c
	rm -f ../bin/motorboard
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard.c

allOn: /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_allOn.c
	rm -f ../bin/motorboard_allOn
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard_allOn motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_allOn.c

forward: /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallForward.c
	rm -f ../bin/motorboard_forward
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard_forward motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallForward.c

left: /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallLeft.c
	rm -f ../bin/motorboard_left
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard_left motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallLeft.c

back: /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallBack.c
	rm -f ../bin/motorboard_back
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard_back motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallBack.c

right: /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallRight.c
	rm -f ../bin/motorboard_right
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -lpthread -o ../bin/motorboard_right motorboard.c mot.c ../gpio/gpio.c ../util/util.c main_motorboard_fallRight.c

clean:
	rm -f ../bin/motorboard*