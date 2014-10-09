/*
 controlthread.c - AR.Drone control thread

 Copyright (C) 2011 Hugo Perquin - http://blog.perquin.com

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA 02110-1301 USA.
 */

#define _GNU_SOURCE
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>  //exit()
#include <pthread.h>
#include <math.h>
#include <sched.h>

#include "../util/type.h"
#include "../util/util.h"
#include "../motorboard/motorboard.h"
#include "../udp/udp.h"
#include "controlthread.h"
#include "controls.h"
#include "control_strategies/pid_strategy.h"

pthread_t ctl_thread;
pthread_attr_t ctl_attrs;

struct drone_state_struct ds;

struct control_strategy_struct control_strategy;

int i = 0;

float motor[4];

#define MAX_LOGBUFSIZE 1024

struct udp_struct udpNavLog;
int logcnt = 0;
void navLog_Send();
void *ctl_thread_main(void* data);

int ctl_Init(char *client_addr) {

	struct sched_param params;
	params.sched_priority = 99;

	LOAD_STRATEGY(control_strategy, pid_strategy);

	//defaults from AR.Drone app:  pitch,roll max=12deg; yawspeed max=100deg/sec; height limit=on; vertical speed max=700mm/sec; 
	ds.control_limits.pitch_roll_max = DEG2RAD(12); //degrees     
	//control_limits.yawsp_max=DEG2RAD(100); //degrees/sec
	ds.control_limits.h_max = 6.00;
	ds.control_limits.h_min = 0.40;
	ds.control_limits.throttle_hover = 0.55;
	ds.control_limits.throttle_min = 0.01;
	ds.control_limits.throttle_max = 0.85;
	ds.control_limits.adj_yaw_max = 0.1;

	//Attitude Estimate
	int rc = att_Init(&ds.att);
	if (rc)
		return rc;

//	rc = horizontal_velocities_init(&ds.hor_velocities);
//	if (rc)
//		return rc;

	//udp logger
	if (client_addr) {
		udpClient_Init(&udpNavLog, client_addr, 7778);
		navLog_sendLogHeaders();
		navLog_Send();
		printf("udpClient_Init %d\n", rc);
	}

	//start motor thread
	rc = motorboard_Init();
	if (rc)
		return rc;

	control_strategy.init();

	if (pthread_attr_init(&ctl_attrs)) perror("pthread_attr_init");
	if (pthread_attr_setinheritsched(&ctl_attrs, PTHREAD_EXPLICIT_SCHED)) perror("pthread_attr_setinheritsched");
	if (pthread_attr_setschedpolicy(&ctl_attrs, SCHED_RR)) perror("pthread_attr_setschedpolicy");
	if (pthread_attr_setschedparam(&ctl_attrs, &params)) perror("pthread_attr_setschedparam");
	rc = pthread_create(&ctl_thread, &ctl_attrs, ctl_thread_main, NULL);
	if (rc) {
		printf("ctl_Init: Return code from pthread_create(control_thread) is %d\n",
				rc);
		return 202;
	}
	return 0;
}

void *ctl_thread_main(void* data) {
	int cnt = 0;
	int rc;
	struct sched_param param;
	int policy;
	switchState(&ds, Landed);
	pthread_getschedparam(pthread_self(), &policy, &param);
	printf("thread policy: %d, prio: %d\n", policy, param.sched_priority);
	while (1) {
		rc = att_GetSample(&ds.att);
		if (!rc) {
//			horizontal_velocities_getSample(&ds.hor_velocities, &ds.att);
			break;
		}
		if (rc != 1)
			printf("ctl_thread_main: att_GetSample return code=%d\n", rc);

	}

	while (1) {
		//get sample
		//double stop, start = util_timestamp();
		while (1) {
			rc = att_GetSample(&ds.att); //non blocking call
			if (!rc) {
//				horizontal_velocities_getSample(&ds.hor_velocities, &ds.att);
				break;
			}
			if (rc != 1)
				printf("ctl_thread_main: att_GetSample return code=%d\n", rc);
		}

		control_strategy.calculateMotorSpeeds(&ds, motor);

		//send to motors
		motorboard_Run(motor[0], motor[1], motor[2], motor[3]);

		if ((cnt % 200) == 0) {
			printf("SET ROLL %5.2f PITCH %5.2f YAW %5.2f   H %5.2f\n",
					ds.setpoint.roll, ds.setpoint.pitch, ds.setpoint.yaw,
					ds.setpoint.h);
			printf("ATT ROLL %5.2f PITCH %5.2f YAW %5.2f   H %5.2f\n",
					ds.att.roll, ds.att.pitch, ds.att.yaw, ds.att.h);
		}

		//blink leds    
		cnt++;
		if ((cnt % 200) == 0)
			motorboard_SetLeds(MOT_LEDGREEN, MOT_LEDGREEN, MOT_LEDGREEN, MOT_LEDGREEN);
		else if ((cnt % 200) == 100)
			motorboard_SetLeds(0, 0, 0, 0);

		navLog_Send();

		//yield to other threads
		//stop = util_timestamp();
		//printf("ctl_thread_main loop iteration took: %f ms\n",
		//		( stop - start)* 1000);
		pthread_yield ()
	;}
return NULL;
}
//logging

void navLog_sendLogHeaders() {

	char logbuf[MAX_LOGBUFSIZE];
	int logbuflen;

	logbuflen = snprintf(logbuf, MAX_LOGBUFSIZE, "cnt,"
			"flyState,"
			"setpoint.h [m],"
			"setpoint.pitch [deg],"
			"setpoint.roll [deg],"
			"setpoint.yaw [deg],"
			"motval_avg [frac],"
			"motval_0 [frac],"
			"motval_1 [frac],"
			"motval_2 [frac],"
			"motval_3 [frac],"
			"hor_velocities.xv,"
			"hor_velocities.yv,"
			"hor_velocities.dt,"
			"hor_velocities.seqNum");
	logbuflen += att_getLogHeadings(logbuf + logbuflen, MAX_LOGBUFSIZE - logbuflen);
	logbuflen += control_strategy.getLogHeadings(logbuf + logbuflen, MAX_LOGBUFSIZE - logbuflen);
	udpClient_Send(&udpNavLog, logbuf, logbuflen);
}

void navLog_Send() {
	char logbuf[MAX_LOGBUFSIZE];
	int logbuflen;

	float motval[4];
	motorboard_GetMot(motval);

	logcnt++;
	logbuflen = snprintf(
			logbuf,
			MAX_LOGBUFSIZE,
			"%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%ld"
			, logcnt
			, ds.flyState
			, ds.setpoint.h// setpoint height
			,RAD2DEG(ds.setpoint.pitch) //setpoint pitch [deg]
			,RAD2DEG(ds.setpoint.roll)//setpoint roll [deg]
			,RAD2DEG(ds.setpoint.yaw)//yaw pitch [deg]
			,(motval[0] + motval[1] + motval[2] + motval[3]) *0.25//thro ttle setting 0.00 - 1.00
			, motval[0], motval[1], motval[2], motval[3],
			ds.hor_velocities.xv, ds.hor_velocities.yv,
			ds.hor_velocities.dt, ds.hor_velocities.seqNum);

		logbuflen += att_getLogText(&ds.att,logbuf + logbuflen,MAX_LOGBUFSIZE - logbuflen);
		logbuflen += control_strategy.getLogText(logbuf + logbuflen,MAX_LOGBUFSIZE - logbuflen);
		udpClient_Send(&udpNavLog, logbuf, logbuflen);
}

int ctl_FlatTrim() {
	return att_FlatTrim(&ds.att);
}

void ctl_SetSetpoint(float pitch, float roll, float yaw, float h) {
	if (pitch > ds.control_limits.pitch_roll_max)
	pitch = ds.control_limits.pitch_roll_max;
	if (pitch < -ds.control_limits.pitch_roll_max)
	pitch = -ds.control_limits.pitch_roll_max;
	ds.setpoint.pitch = pitch;
	if (roll > ds.control_limits.pitch_roll_max)
	roll = ds.control_limits.pitch_roll_max;
	if (roll < -ds.control_limits.pitch_roll_max)
	roll = -ds.control_limits.pitch_roll_max;
	ds.setpoint.roll = roll;
	//if(yaw > control_limits.yawsp_max) yaw = control_limits.yawsp_max;
	//if(yaw < -control_limits.yawsp_max) yaw = -control_limits.yawsp_max;
	ds.setpoint.yaw = yaw;
	if (h > ds.control_limits.h_max)
	h = ds.control_limits.h_max;
	if (h <= 0)
	h = 0;
	if (h > 0 && h < ds.control_limits.h_min)
	h = ds.control_limits.h_min;
	ds.setpoint.h = h;
}

void ctl_SetSetpointDiff(float pitch, float roll, float yaw, float h) {
	ctl_SetSetpoint(pitch + ds.setpoint.pitch, ds.setpoint.pitch + pitch,
	yaw + ds.setpoint.yaw, h + ds.setpoint.h);
}

void ctl_Close() {
	motorboard_Close();
	att_Close();
}
