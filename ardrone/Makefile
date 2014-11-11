all: clean attitude gpio motorboard navboard vbat
	clear

attitude: attitude/Makefile
	$(MAKE) -C attitude all

fly: fly/Makefile
	$(MAKE) -C fly all

gpio: gpio/Makefile
	$(MAKE) -C gpio all

motorboard: motorboard/Makefile
	$(MAKE) -C motorboard all

navboard: navboard/Makefile
	$(MAKE) -C navboard all

udp: udp/Makefile
	$(MAKE) -C udp all

vbat: vbat/Makefile
	$(MAKE) -C vbat all

video: video/Makefile
	$(MAKE) -C video all

clean:
	rm -rf bin

.PHONY: all