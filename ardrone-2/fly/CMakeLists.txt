cmake_minimum_required(VERSION 2.6)

include (../ardrone2_toolchain.cmake )

link_libraries(pthread)
link_directories(${CMAKE_BINARY_DIR}/../libs/orocos-bfl-0.8.0/src)
link_libraries(m)
link_libraries(orocos-bfl)

include_directories(${CMAKE_BINARY_DIR}/../libs/orocos-bfl-0.8.0/src
	${CMAKE_BINARY_DIR}/../libs/boost_1_50_0
)


SET( FLY_SOURCES 	main_fly.c
	controlthread.c
	control_strategies/pid_strategy.c
	control_strategies/pid.c
	controls.c
	flyparams.c
	../navboard/navboard.c
	../util/util.c
	../gpio/gpio.c
	../motorboard/motorboard.c
	../udp/udp.c
	../attitude/attitude.cpp
	../attitude/DroneKalman.cpp
	../attitude/ars.c
	../attitude/moving_average.c
	../horizontal_velocities/horizontal_velocities.c
	../video/video.c
	../video/blocksum.c
	../lowpass/lowpass.c
)

add_executable(fly
	${FLY_SOURCES}
)

add_executable(nofly
	${FLY_SOURCES}
)
SET_TARGET_PROPERTIES (nofly PROPERTIES COMPILE_FLAGS "-DMOTOR_DRY_RUN")


	

