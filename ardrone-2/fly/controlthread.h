/*
    controlthread.h - AR.Drone control thread

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
#ifndef _CONTROLTRHEAD_H
#define _CONTROLTRHEAD_H

#ifdef __cplusplus
extern "C" {
#endif

/** initialises the control thread
 * must be called before any other ctl_ function
 * may not be called twice
 * @param client_addr the internet address of a machine to receive log data via udp
 */
int ctl_Init(char *client_addr);
/** calibrates the sensor offsets, only to be called when the drone is on flat ground */
int ctl_FlatTrim();
/** requests the drone to turn into a certain pose */
void ctl_SetSetpoint(float pitch, float roll, float yawsp, float h);
/** requests a diffential change of drone pose */
void ctl_SetSetpointDiff(float pitch, float roll, float yaw, float h);
/** stops / closes the drone thread
* no ctl_* functions may be called afterward
*/
void ctl_Close();

/** private function to send the header data of the log file */
void navLog_sendLogHeaders();


#ifdef __cplusplus
}
#endif


#endif
