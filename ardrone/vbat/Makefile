FILE = ../compiler_loc.dat
LOC = $(shell cat ${FILE})

all: clean vbat

setup:
	mkdir -p ../bin/vbat

vbat: setup vbat.c main_vbat.c
	$(LOC) -o ../bin/vbat/vbat vbat.c main_vbat.c

clean:
	rm -rf ../bin/vbat