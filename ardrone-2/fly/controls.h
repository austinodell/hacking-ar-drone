#ifndef _CONTROLS_H
#define _CONTROLS_H

#include "../attitude/attitude.h"
#include "../horizontal_velocities/horizontal_velocities.h"


struct setpoint_struct {
	float pitch; //radians  
	float roll; //radians     
	float yaw; //radians   
	float h; //meters
};


struct control_limits_struct {
	float pitch_roll_max; //radians     
	float h_max; //m
	float h_min; //m
	float throttle_hover; //hover throttle setting
	float throttle_min; //min throttle (while flying)
	float throttle_max; //max throttle (while flying)
	float adj_yaw_max;  //max yaw influence
};


enum FlyState {
	Landed=1,
	Launching=10,
	Flying=11,
	Landing=12,
	Error=20
};


/** returns the name of a given state */
const char *stateName(enum FlyState state);


/** a structure containing the full state of the drone */
struct drone_state_struct {
	struct att_struct att;
	struct horizontal_velocities_struct hor_velocities;
	enum FlyState flyState;
	struct setpoint_struct setpoint;
	struct control_limits_struct control_limits;
};

/** switches the drone movement state machine to a new state */
void switchState(struct drone_state_struct *dronestate, enum FlyState newState);

struct control_strategy_struct {
	/** called once */
	void (*init)();
	/** called every time new attitude data is available, should write desired motor velocities to the float-array */
	void (*calculateMotorSpeeds)(struct drone_state_struct *, float[4]);
	/** should write upto maxLen (second parm) bytes into the char * and return number of bytes written (including \0) */
	unsigned int (*getLogText)(char *,unsigned int);
	/** should write upto maxLen (second parm) bytes into the char * and return number of bytes written (including \0) */
	unsigned int (*getLogHeadings)(char *,unsigned int);
};


#define SET_FPTR(targetStruct, prfx, funcName) \
	targetStruct.funcName = prfx ## _ ## funcName;

#define LOAD_STRATEGY(targetStruct, name) \
	do { \
		SET_FPTR(targetStruct, name, init); \
		SET_FPTR(targetStruct, name, calculateMotorSpeeds); \
		SET_FPTR(targetStruct, name, getLogText); \
		SET_FPTR(targetStruct, name, getLogHeadings); \
	} while(0)	

#endif
