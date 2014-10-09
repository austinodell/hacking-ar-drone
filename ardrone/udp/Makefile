FILE = ../compiler_loc.dat
LOC = $(shell cat ${FILE})

all: clean udpserver udpclient

setup:
	mkdir -p ../bin/udp

udpserver: setup udp.c main_udpserver.c
	$(LOC) -o ../bin/udp/udpserver udp.c main_udpserver.c

udpclient: setup udp.c main_udpclient.c
	$(LOC) -o ../bin/udp/udpclient udp.c main_udpclient.c

clean:
	rm -rf ../bin/udp