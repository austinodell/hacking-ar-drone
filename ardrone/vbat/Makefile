all: clean vbat

setup:
	mkdir -p ../bin/vbat

vbat: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ vbat.c main_vbat.c
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -o ../bin/vbat/vbat vbat.c main_vbat.c

clean:
	rm -rf ../bin/vbat