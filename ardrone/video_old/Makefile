FILE = ../compiler_loc.dat
LOC = $(shell cat ${FILE})

all: clean video

setup:
	mkdir -p ../bin/video

video: setup ../util/util.c video.c main_video.c
	$(LOC) -o ../bin/video/video -lpthread ../util/util.c video.c main_video.c blocksum.c

clean:
	rm -rf ../bin/video