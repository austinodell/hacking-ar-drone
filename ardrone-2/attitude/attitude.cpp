/*
 attitude.c - AR.Drone attitude estimate driver

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
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>  //exit()
#include <math.h>

#include "../util/type.h"
#include "../navboard/navboard.h"
#include "../util/util.h"
#include "ars.h"
#include "attitude.h"
#include "DroneKalman.h"

float lr_a;
float lr_b;
int lr_n;
int lr_off;
float lr_y[3];

//init linear regession for n values
void lr_init(int n) {
	lr_n = n;
	float sx = 0;
	float sxx = 0;
	for (int i = 0; i < n; i++) {
		sx += i;
		sxx += i * i;
		lr_y[i] = 0;
	}
	lr_a = sx / n;
	lr_b = sxx - sx * sx / n;
}

//calc slope for next y value
float lr_slope(float y) {
	float sxy = 0;
	float sy = 0;
	lr_y[lr_off] = y;
	lr_off = (lr_off + 1) % lr_n;
	for (int i = 0; i < lr_n; i++) {
		int ii = (i + lr_off) % lr_n;
		sy += lr_y[ii];
		sxy += lr_y[ii] * i;
	}
	return (sxy - lr_a * sy) / lr_b;
}

//struct ars_Gyro1DKalman ars_roll[B;
//struct ars_Gyro1DKalman ars_pitch;

DroneKalman dk_roll(0.0001/*Q_angle*/, 0.001/*Q_angelvel*/, 0.0000001/*Q_drift */, 10.0/*R_accelero*/,0.22/*R_gyro*/);
DroneKalman dk_pitch(0.0001/*Q_angle*/, 0.001/*Q_angelvel*/, 0.0000001/*Q_drift */, 10.0/*R_accelero*/,0.22/*R_gyro*/);

//roll angle from acc in radians
float roll(float a_z, float a_y) {
	return atan2(a_y, -a_z);
}

//pitch angle from acc in radians
float pitch(float a_z, float a_x) {
	return atan2(a_x, -a_z);
}

void att_Print(struct att_struct *att) {
	printf(
			"roll=%5.1f,a=%5.1f,g=%5.1f pitch=%5.1f,a=%5.1f,g=%5.1f yaw=%5.1f h=%5.3f dt=%4.1f\n",
			RAD2DEG(att->roll), RAD2DEG(att->roll_a), RAD2DEG(att->roll_g),
			RAD2DEG(att->pitch), RAD2DEG(att->pitch_a), RAD2DEG(att->pitch_g),
			RAD2DEG(att->yaw), att->h, att->dt * 1000);
}

float last_h;
float last_ts;

int att_GetSample(struct att_struct *att) {
	int rc;

	//get nav sample
	rc = nav_GetSample(&att->navdata);
	if (rc)
		return rc;

	att->dt=att->navdata.dt;

	//smooth out missing h samples
	if (abs(att->navdata.h - last_h) > 0.05 && last_ts - att->navdata.ts < 0.10) {
		att->h = last_h;
	} else {
		att->h = att->navdata.h;
		last_h = att->navdata.h;
		last_ts = att->navdata.ts;
	}
	if (att->navdata.h_meas) {
		att->hv = lr_slope(att->h) * 25; //25Hz sample rate
	}

	//update att
	att->roll_g += att->navdata.gx * att->dt;
	att->pitch_g += att->navdata.gy * att->dt;
	att->yaw += att->navdata.gz * att->dt;
	att->roll_a = roll(att->navdata.az, att->navdata.ay);
	att->pitch_a = pitch(att->navdata.az, att->navdata.ax);

	// remove motor noise	
	att->filtered_gx=lowpass_update(&att->gx_filter,att->navdata.gx);
	att->filtered_gy=lowpass_update(&att->gy_filter,att->navdata.gy);

	//execute kalman roll filter
	dk_roll.update(att->roll_a, att->filtered_gx);
	att->roll = dk_roll.angle();
	att->roll_vel_kalman = dk_roll.angleVel();
	att->gx_bias_kalman = dk_roll.drift();

	//execute kalman pitch filter
	dk_pitch.update(att->pitch_a, att->filtered_gy);
	att->pitch = dk_pitch.angle();
	att->pitch_vel_kalman = dk_pitch.angleVel();
	att->gy_bias_kalman = dk_pitch.drift();

	return 0;
}

int att_FlatTrim(struct att_struct *att) {
	int rc;
	//calibrate
	printf("Calibrating Navboard ...\n");
	rc = nav_FlatTrim();
	if (rc)
		printf("Failed: retcode=%d\r\n", rc);
	else
		printf("Calibrate Navboard OK\n");

	//init ars
	//ars_Init(&ars_roll,  0.001/*Q_angle*/, 0.0000003/*Q_gyro*/, 100/*R_angle*/);
	//ars_Init(&ars_pitch, 0.001/*Q_angle*/, 0.0000003/*Q_gyro*/, 100/*R_angle*/);

	//clear att
	att->pitch_g = 0;
	att->pitch_a = 0;
	att->pitch = 0;
	att->roll_g = 0;
	att->roll_a = 0;
	att->roll = 0;
	att->yaw = 0;
	att->h = 0;
	att->dt = 0;

	return rc;
}

int att_Init(struct att_struct *att) {
	int rc;

	lr_init(3);

	//nav board
	printf("Init Navboard ...\n");
	rc = nav_Init(&att->navdata);
	if (rc)
		return rc;

	rc = nav_GetSample(&att->navdata);
	if (rc)
		return rc;
	last_ts = att->navdata.ts;
	last_h = att->navdata.h;
	lowpass_init(&att->gx_filter);
	lowpass_init(&att->gy_filter);

	printf("Init Navboard OK\n");

	att_FlatTrim(att);
	return 0;
}

void att_Close() {
	nav_Close();
}

unsigned int att_getLogHeadings(char *buf, unsigned int maxLen) {
	int len;
	len = snprintf(buf, maxLen, ","
			"att.ts [s],"
			"att.ax [m/s^2],"
			"att.ay [m/s^2],"
			"att.az [m/s^2],"
			"att.gx [deg/s],"
			"att.filtered_gx [deg/s],"
			"att.gx_bias_kalman [deg/s],"
			"att.gy [deg/s],"
			"att.filtered_gy [deg/s],"
			"att.gy_bias_kalman [deg/s],"
			"att.gz [deg/s],"
			"att.hv [m/sec],"
			"att.h [m],"
			"att.pitch [deg],"
			"att.pitch_vel_kalman [deg/s],"
			"att.roll [deg],"
			"att.roll_vel_kalman [deg/s],"
			"att.yaw [deg],"
			"att.magx [deg],"
			"att.magy [deg],"
			"att.magz [deg]"
			);
	return len;
}

unsigned int att_getLogText(struct att_struct *att, char *buf, unsigned int maxLen) {
	int len;
	len= snprintf(buf,maxLen,
			",%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f"
			,att->navdata.ts // navdata timestamp in sec
			,att->navdata.ax// acceleration x-axis in [m/s^2] front facing up is positive
			,att->navdata.ay// acceleration y-axis in [m/s^2] left facing up is positive
			,att->navdata.az// acceleration z-axis in [m/s^2] top facing up is positive
			,RAD2DEG(att->navdata.gx)// gyro value x-axis in [deg/sec] right turn, i.e. roll right is positive
			,RAD2DEG(att->filtered_gx)// lowpass filtered gyro value x-axis in [deg/sec] right turn, i.e. roll right is positive
			,RAD2DEG(att->gx_bias_kalman)// estimated bias of gyro value x-axis in [deg/sec] right turn, i.e. roll right is positive
			,RAD2DEG(att->navdata.gy)// gyro value y-axis in [deg/sec] right turn, i.e. pitch down is positive
			,RAD2DEG(att->filtered_gy)// lowpass filtered gyro value y-axis in [deg/sec] right turn, i.e. pitch down is positive
			,RAD2DEG(att->gy_bias_kalman)// estimated bias of gyro value y-axis in [deg/sec] right turn, i.e. pitch down is positive
			,RAD2DEG(att->navdata.gz)// gyro value z-axis in [deg/sec] right turn, i.e. yaw left is positive
			,att->hv// vertical speed [m/sec]
			,att->h// actual height above ground in [m]
			,RAD2DEG(att->pitch)//actual pitch
			,RAD2DEG(att->pitch_vel_kalman)// filtered gyro value x-axis in [deg/sec] right turn, i.e. roll right is positive
			,RAD2DEG(att->roll)//actual roll
			,RAD2DEG(att->roll_vel_kalman)// filtered gyro value y-axis in [deg/sec] right turn, i.e. pitch down is positive
			,RAD2DEG(att->yaw)//actual yaw
			,att->navdata.mag_x// magnet x-axis in [deg]
			,att->navdata.mag_y// magnet y-axis in [deg]
			,att->navdata.mag_z// magnet z-axis in [deg]


	);
	return len;

}

