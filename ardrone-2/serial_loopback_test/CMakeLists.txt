cmake_minimum_required(VERSION 2.6)

include ( ../ardrone2_toolchain.cmake )

link_libraries(m)
link_libraries(pthread)

add_executable(serial_loopback_test
	main_loopback_test.c
	../util/util.c
)

	

