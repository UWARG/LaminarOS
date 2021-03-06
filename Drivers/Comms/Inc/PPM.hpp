/*
 * LOS_Link.hpp
 *
 *  Created on: May 24, 2022
 *      Author: anthony
 */

#ifndef PPM_HPP_
#define PPM_HPP_


#include "../../Actuators/Inc/PWM.hpp"
#include <stdint.h>
#include "../../driver_params.hpp"

static const uint8_t MAX_PPM_CHANNELS = 12; // TODO: put this into driver_params

static const int32_t ARM_DISARM_CHANNEL_INDEX = 4;
static const uint8_t GIMBAL_GRABBER_TOGGLE_INDEX = 5; // three-way switch for gimbal, grabber, or none
static const uint8_t LEFT_GIMBAL_GRABBER_CRANE = 6;
static const uint8_t RIGHT_GIMBAL_GRABBER_MOUTH = 7;

enum StatusCode{STATUS_CODE_OK, STATUS_CODE_FAILED, STATUS_CODE_INVALID_ARGS};

typedef struct PPM_Instructions_t
{
    uint8_t PPMValues[MAX_PPM_CHANNELS];
} PPM_Instructions_t;

class PPMChannel {
 public:
	/**
	 * How many channels are we expecting in the input port?
	 * Usually this is only 8
	 * @param num_channels
	 * @param disconnect_timeout Number of ms to wait before we consider channel disconnected
	 */
	explicit PPMChannel(uint8_t num_channels = 8, uint32_t disconnect_timeout = 1000);

	/**
	 * Reconfigure number of channels
	 * @param num_channels
	 */
	StatusCode setNumChannels(uint8_t num_channels);

	/**
	 * Set expected input limits for a particular channel
	 * @param channel
	 * @param min Min time in us (for a 0% signal)
	 * @param max Max time in us (for 100% signal)
	 * @param deadzone time in us for deadzone. ie. if deadzone is set to 50, a signal that is received
	 * 		with a 1050us length will still be considered 0%
	 */
	StatusCode setLimits(uint8_t channel, uint32_t min, uint32_t max, uint32_t deadzone);

	// /**
	//  * Set the disconnect timeout
	//  * @param timeout
	//  * @return
	//  */
	// StatusCode setTimeout(uint32_t timeout);

	/**
	 * Returns a percent value that was most recently received from the PPM channel, as a percentage
	 * from 0-100
	 * @param num
	 * @return 0 if an invalid channel number was given
	 */
	uint8_t get(PWMChannelNum num);

	/**
	 * Same as above function, but returns the captured value in microseconds instead
	 * @param num
	 * @return 0 if an invalid channel number was given
	 */
	uint32_t get_us(PWMChannelNum num);

	/**
	 * Wether the channel has disconnected based on the timeout
	 * @param sys_time Current system time in ms
	 * @return
	 */
	bool is_disconnected(uint32_t sys_time);

 private:
 	PWMChannelNum num_channels = 0;
	float min_values[MAX_PPM_CHANNELS]; //stores min microsecond values for each channel
	float max_values[MAX_PPM_CHANNELS]; //stores max microsecond values for each channel
	uint32_t disconnect_timeout;
	bool is_setup = false;

//	uint32_t counter_to_time(uint16_t count, uint32_t psc);
//	uint8_t time_to_percentage(uint32_t max, uint32_t min, uint32_t deadzone, uint32_t time);

};




#endif /* PPM_HPP_ */
