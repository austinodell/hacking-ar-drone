all: clean udpserver udpclient

setup:
	mkdir -p ../bin/udp

udpserver: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ udp.c main_udpserver.c
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -o ../bin/udp/udpserver udp.c main_udpserver.c

udpclient: /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ udp.c main_udpclient.c
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -o ../bin/udp/udpclient udp.c main_udpclient.c

clean:
	rm -rf ../bin/udp