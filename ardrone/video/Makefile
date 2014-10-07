all: clean video

setup:
	mkdir -p ../bin/video

video: setup /usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ ../util/util.c video.c main_video.c
	/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ -o ../bin/video/video -lpthread ../util/util.c video.c main_video.c

clean:
	rm -rf ../bin/video