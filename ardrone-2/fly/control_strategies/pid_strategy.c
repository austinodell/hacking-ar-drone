#include "pid.h"
#include "../controls.h"
#include "../../util/util.h"
#include "pid_strategy.h"
#include "../flyparams.h"
#include <stdio.h>

struct pid_struct pid_roll;
struct pid_struct pid_pitch;
struct pid_struct pid_yaw;

struct pid_struct pid_roll_vel;
struct pid_struct pid_pitch_vel;

struct pid_struct pid_hor_vel_x;
struct pid_struct pid_hor_vel_y;

struct pid_struct pid_hor_pos_x;
struct pid_struct pid_hor_pos_y;

struct pid_struct pid_h;

double targetXVel = 0;
double targetYVel = 0;

double target_pitch_vel = 0;
double target_roll_vel = 0;

double targetRoll = 0;
double targetPitch = 0;

float adj_roll;
float adj_pitch;
float adj_yaw;
float adj_h;

struct lowpass_struct lp_adj_h;
struct lowpass_struct lp_adj_roll;
struct lowpass_struct lp_adj_pitch;
struct lowpass_struct lp_adj_yaw;

float throttle;

// minimum throttle for launching ramp 
#define MOTOR_INIT_THROTTLE 0.1
// ramp end throttle
#define MOTOR_TAKEOF_THROTTLE 0.55
/** ramp progress while launching*/
#define LAUNCHRAMP_LENGTH 600 // 200 ^= 1 second
int launchRamp = 0;

// when landing, start ramp below this height over ground
#define LANDING_HEIGHT_START_RAMP 0.35

// throttle for landing part below min flight height (now height info)
#define MOTOR_LAND_MAX_THROTTLE  0.50
// ramp end throttle
#define MOTOR_LAND_MIN_THROTTLE 0.1
/** ramp progress while landing*/
#define LANDRAMP_LENGTH 300 // 200 ^= 1 second
int landRamp = 0;

double xPos;
double yPos;

struct setpoint_struct setpoint_landing = { 0, 0, 0, 0.2 };

void pid_strategy_init() {

	//init pid pitch/roll 
	pid_Init(&pid_roll,  getFloatParam("PID_ROLL_KP",2.0) , getFloatParam("PID_ROLL_I",0.0) , getFloatParam("PID_ROLL_D",0.0),  getFloatParam("PID_ROLL_I_MAX",  0.5));
	pid_Init(&pid_pitch, getFloatParam("PID_PITCH_KP",2.0), getFloatParam("PID_PITCH_I",0.0), getFloatParam("PID_PITCH_D",0.0), getFloatParam("PID_PITCH_I_MAX", 0.5));
	pid_Init(&pid_yaw,   getFloatParam("PID_YAW_KP",2.0),	getFloatParam("PID_YAW_I",0.0),   getFloatParam("PID_YAW_D",0.0),   getFloatParam("PID_YAW_I_MAX",   0.5));

	pid_Init(&pid_roll_vel,  getFloatParam("PID_ROLL_VEL_KP",0.2) , getFloatParam("PID_ROLL_VEL_I",0.0) , getFloatParam("PID_ROLL_VEL_D",0.0) , getFloatParam("PID_ROLL_VEL_I_MAX"  ,0.5));
	pid_Init(&pid_pitch_vel, getFloatParam("PID_PITCH_VEL_KP",0.2), getFloatParam("PID_PITCH_VEL_I",0.0), getFloatParam("PID_PITCH_VEL_D",0.0), getFloatParam("PID_PITCH_VEL_I_MAX" ,0.5));

	/** @todo these need an i-part */
	pid_Init(&pid_hor_vel_x, 0.2, 0.01, 0, 0.1);
	pid_Init(&pid_hor_vel_y, 0.2, 0.01, 0, 0.1);

	/** @todo these need an i-part */
	pid_Init(&pid_hor_pos_x, 5.0, 0.0, 0, 1);
	pid_Init(&pid_hor_pos_y, 5.0, 0.0, 0, 1);

	pid_Init(&pid_h, getFloatParam("PID_H_KP",0.03), getFloatParam("PID_H_I",0.01), 0, getFloatParam("PID_H_I_MAX", 0.1));

	lowpass_init(&lp_adj_h);
	lowpass_init(&lp_adj_roll);
	lowpass_init(&lp_adj_pitch);
	lowpass_init(&lp_adj_yaw);


	throttle = 0.00;

}

void pidStrategy_calculateMotorSpeedsFlying(struct horizontal_velocities_struct *hv, struct att_struct *att, struct setpoint_struct *setpoint, struct control_limits_struct *control_limits, float motorOut[4]) {
	/* overwrite setpoints for now */
	targetRoll = setpoint->roll;
	targetPitch = setpoint->pitch;

	if (0) {
		targetXVel = pid_Calc(&pid_hor_pos_x, 0 - xPos, att->dt);
		targetYVel = pid_Calc(&pid_hor_pos_y, 0 - yPos, att->dt);

		targetPitch = pid_Calc(&pid_hor_vel_x, targetXVel - hv->xv, att->dt);
		targetRoll = pid_Calc(&pid_hor_vel_y, targetYVel - hv->yv, att->dt);
	}

	//flying, calc pid controller corrections
	target_roll_vel  = pid_Calc(&pid_roll, targetRoll  - att->roll , att->dt); //err positive = need to roll right
	target_pitch_vel = pid_Calc(&pid_pitch,targetPitch - att->pitch, att->dt); //err positive = need to pitch down

	adj_yaw = pid_Calc(&pid_yaw, setpoint->yaw - att->yaw, att->dt); //err positive = need to increase yaw to the left

	adj_roll  = pid_Calc(&pid_roll_vel , target_roll_vel  - att->filtered_gx, att->dt); //err positive = need to roll right
	adj_pitch = pid_Calc(&pid_pitch_vel, target_pitch_vel - att->filtered_gy, att->dt); //err positive = need to pitch down

	adj_h = pid_CalcD(&pid_h, setpoint->h - att->h, att->dt, att->hv); //err positive = need to increase height


	// apply lowpass-filter
	
	adj_h    =lowpass_update(&lp_adj_h    , adj_h    );
	adj_roll =lowpass_update(&lp_adj_roll , adj_roll );
	adj_pitch=lowpass_update(&lp_adj_pitch, adj_pitch);
	adj_yaw  =lowpass_update(&lp_adj_yaw  , adj_yaw  );

	throttle = control_limits->throttle_hover + adj_h;
	if (throttle < control_limits->throttle_min)
		throttle = control_limits->throttle_min;
	if (throttle > control_limits->throttle_max)
		throttle = control_limits->throttle_max;

	if (adj_yaw > control_limits->adj_yaw_max)
		adj_yaw = control_limits->adj_yaw_max;
	if (adj_yaw < -control_limits->adj_yaw_max)
		adj_yaw = -control_limits->adj_yaw_max;
		
		
		
	//convert pid adjustments to motor values
	motorOut[0] = throttle + adj_roll - adj_pitch + adj_yaw;
	motorOut[1] = throttle - adj_roll - adj_pitch - adj_yaw;
	motorOut[2] = throttle - adj_roll + adj_pitch + adj_yaw;
	motorOut[3] = throttle + adj_roll + adj_pitch - adj_yaw;
	
	// do not allow to turn of the motors while flying
	int i;
	for(i=0;i<4;i++) if(motorOut[i] < 0.05) motorOut[i]=0.05;
	
}

void pid_strategy_calculateMotorSpeeds(struct drone_state_struct *cs, float motorOut[4]) {
	struct setpoint_struct * setpoint = &cs->setpoint;
	switch (cs->flyState) {
	case Landed:
		for (int i = 0; i < 4; i++)
			motorOut[i] = 0;
		if (setpoint->h > 0)
			switchState(cs, Launching);
		launchRamp = 0;
		landRamp = 0;
		break;
	case Launching:
		launchRamp++;
		for (int i = 0; i < 4; i++)
			motorOut[i] = launchRamp * (MOTOR_TAKEOF_THROTTLE - MOTOR_INIT_THROTTLE) / LAUNCHRAMP_LENGTH + MOTOR_INIT_THROTTLE;

		if (cs->att.h > 0 || launchRamp > LAUNCHRAMP_LENGTH) {
			xPos = 0;
			yPos = 0;
			launchRamp = 0;
			switchState(cs, Flying);
		}
		if (setpoint->h < 0.1)
			switchState(cs, Landing);
		break;

	case Flying:
		xPos += cs->hor_velocities.xv * cs->att.dt;
		yPos += cs->hor_velocities.yv * cs->att.dt;

		pidStrategy_calculateMotorSpeedsFlying(&cs->hor_velocities, &cs->att, setpoint, &cs->control_limits, motorOut);
		if (setpoint->h < 0.1)
			switchState(cs, Landing);
		break;

	case Landing:
		xPos = 0;
		yPos = 0;
		if (cs->att.h > LANDING_HEIGHT_START_RAMP) {
			pidStrategy_calculateMotorSpeedsFlying(&cs->hor_velocities, &cs->att, setpoint, &cs->control_limits, motorOut);
		} else if (landRamp < LANDRAMP_LENGTH) {
			landRamp++;
			for (int i = 0; i < 4; i++)
				motorOut[i] = MOTOR_LAND_MAX_THROTTLE - landRamp * (MOTOR_LAND_MAX_THROTTLE - MOTOR_LAND_MIN_THROTTLE) / LANDRAMP_LENGTH;
		} else {
			landRamp = 0;
			switchState(cs, Landed);
		}
		break;

	case Error:
		for (int i = 0; i < 4; i++)
			motorOut[i] = 0;
		if (setpoint->h == 0)
			switchState(cs, Landed);
		launchRamp = 0;
		break;
	}
}

unsigned int pid_strategy_getLogHeadings(char *buf, unsigned int maxLen) {
	int len;
	len = snprintf(buf, maxLen, ","
			"xPos [m],"
			"yPos [m],"
			"targetXVel [m/s],"
			"targetYVel [m/s],"
			"targetPitch [deg],"
			"targetRoll [deg],"
			"targetPitchVel [deg/s],"
			"targetRollVel [deg/s],"
			"adj_pitch,"
			"adj_roll,"
			"adj_yaw,"
			"adj_h");
	return len;
}

unsigned int pid_strategy_getLogText(char *buf, unsigned int maxLen) {
	int len;
	len = snprintf(buf, maxLen, ",%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", xPos, yPos, targetXVel, targetYVel, RAD2DEG(targetPitch), RAD2DEG(targetRoll), RAD2DEG(target_pitch_vel), RAD2DEG(target_roll_vel), adj_pitch, adj_roll, adj_yaw, adj_h);
	return len;
}

