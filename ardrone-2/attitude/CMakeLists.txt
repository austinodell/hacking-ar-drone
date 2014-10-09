cmake_minimum_required(VERSION 2.6)

include (../ardrone2_toolchain.cmake )

link_directories(${CMAKE_BINARY_DIR}/../libs/orocos-bfl-0.8.0/src)
link_libraries(m)
link_libraries(orocos-bfl)

include_directories(${CMAKE_BINARY_DIR}/../libs/orocos-bfl-0.8.0/src
	${CMAKE_BINARY_DIR}/../libs/boost_1_50_0
)

add_executable(attitude
	attitude.cpp
	DroneKalman.cpp
	main_attitude.c
	moving_average.c
	../util/util.c
	../gpio/gpio.c
	ars.c
	../navboard/navboard.c
	../lowpass/lowpass.c
)
