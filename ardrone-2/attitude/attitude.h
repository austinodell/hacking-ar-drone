/*
 attitude.h - AR.Drone attitude estimate driver

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
#ifndef _ATTITUDE_H
#define _ATTITUDE_H

#include "../navboard/navboard.h"
#include "moving_average.h"
#include "../lowpass/lowpass.h"
#ifdef __cplusplus
extern "C" {
#endif

struct att_struct {
    //pitch estimates in radians, positive is pitch down (fly forward)
    float pitch_g; //=sum(gx * dt)
    float pitch_a; //=pitch(az,ax)
    float pitch; //kalman pitch estimate from gy and pitch_a

    //roll estimates in radians, positive is roll right (fly rightward)
    float roll_g; //=sum(gy * dt)
    float roll_a; //=roll(az,ay)
    float roll; //kalman roll estimate from gx and roll_a

    //yaw estimate, positive is yaw left
    float yaw; //=sum(gz * dt)

    //height and speed estimate
    float h; //smoothend hraw
    float hv; //vertical speed in m/sec
    
    double dt; // time since last navdata sample in sec

    struct nav_struct navdata;
    
    struct lowpass_struct gx_filter; // filter for gyro x to remove vibrations by motors
    struct lowpass_struct gy_filter; // filter for gyro y to remove vibrations by motors
    
    float filtered_gx;  // the current output of the gyro x filter
    float filtered_gy;  // the current output of the gyro y filter


    float roll_vel_kalman; // filtered gyro value x-axis in [rad/sec] right turn, i.e. roll right is positive
    float gx_bias_kalman;  // estimated bias for gyro value x-axis in [rad/sec] right turn, i.e. roll right is positive
    
    float pitch_vel_kalman; // filtered gyro value y-axis in [rad/sec] right turn, i.e. pirch down is positive
    float gy_bias_kalman; // estimated bias for gyro value y-axis in [rad/sec] right turn, i.e. pirch down is positive
};

int att_Init(struct att_struct *att);
int att_GetSample(struct att_struct *att);
int att_FlatTrim(struct att_struct *att); //recalibrate
void att_Print(struct att_struct *att);
void att_Close();


/** puts interesting logging information into buffer, returning the number of bytes written, format is csv */
unsigned int att_getLogText(struct att_struct *att,char *buf,unsigned int maxLen);
/* put a list of headings for the log columns into buffer, returning the number of bytes written, format is csv */
unsigned int att_getLogHeadings(char *buf, unsigned int maxLen);

#ifdef __cplusplus
}
#endif

#endif
