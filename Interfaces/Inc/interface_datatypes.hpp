/*
 * interface_datatypes.hpp
 *
 *  Created on: May 25, 2022
 *      Author: anthony
 */

#ifndef INC_INTERFACE_DATATYPES_HPP_
#define INC_INTERFACE_DATATYPES_HPP_


#include <cstdint>

constexpr uint8_t NUM_GPS_WAYPOINTS = 5;
constexpr uint8_t NUM_MOTOR_OUTPUTS = 12;

typedef struct Teleop_Instructions_t{
	float teleop_inp[8]; // deprecated, here just in case
	// should these individual channels be defined in the link or in zp?
	// I think they should be defined in ZP.... (in case you wanted to fly with trims/rates?)
	uint8_t roll;
	uint8_t pitch;
	uint8_t yaw;
	uint8_t throttle;
	uint8_t is_armed;
};

typedef struct Quadrotor_Motor_out {
	float front_left;
	float front_right;
	float back_left;
	float back_right;
};

typedef struct
{
    float frontLeftMotorPercent;
    float frontRightMotorPercent;
    float backLeftMotorPercent;
    float backRightMotorPercent;

} PID_Output_t;

typedef struct GPS_Waypoint_t {
	float latitude;
	float longitude;
	float altitude;
} GPS_Waypoint_t;

typedef struct Data_From_Ground_t {
	bool replaceWaypoints;
	uint8_t GPS_Waypoint_t[NUM_GPS_WAYPOINTS];
} Data_From_Ground_t;

typedef struct Data_To_Ground_t {
	float latitude;
	float longitude;
	float altitude;
	float yaw;
	float pitch;
	float roll;
	uint8_t motorOutputs[NUM_MOTOR_OUTPUTS];
	uint8_t grabberStatus;
} Data_To_Ground_t;

typedef struct Data_From_CV_t {
	uint8_t tempNum;
} Data_From_CV_t;

typedef struct Data_To_CV_t {
	uint8_t tempNum;
} Data_To_CV_t;

typedef struct Data_From_AM_t {
	float latitude;
	float longitude;
	float altitude;
	float yaw;
	float pitch;
	float roll;
	uint8_t motorOutputs[NUM_MOTOR_OUTPUTS];
} Data_From_AM_t;

typedef struct Data_To_AM_t {
	uint8_t tempNum;
} Data_To_AM_t;

#endif /* INC_INTERFACE_DATATYPES_HPP_ */
