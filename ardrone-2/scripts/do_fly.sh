#!/bin/sh
export PID_ROLL_KP=1
export PID_ROLL_I=0.1
export PID_ROLL_I_MAX=0.2
export PID_PITCH_KP=1
export PID_PITCH_I=0.1
export PID_PITCH_I_MAX=0.2
export PID_YAW_KP=0
export PID_YAW_I=0
export PID_YAW_I_MAX=0
export PID_H_KP=0
export PID_H_I=0
export PID_H_I_MAX=0
do_init.sh && fly
