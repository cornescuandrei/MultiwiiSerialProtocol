#ifndef _MSP_H
#define _MSP_H

#include <Arduino.h>

class MSP
{
	public:
		enum MSP_COMMAND
		{
			MSP_ERROR = 0,
			MSP_IDENT = 100,
			MSP_STATUS = 101,
			MSP_RAW_IMU = 102,
			MSP_SERVO = 103,
			MSP_MOTOR = 104,
			MSP_SET_MOTOR = 214,
			MSP_RC = 105,
			MSP_SET_RAW_RC = 200,
			MSP_RAW_GPS = 106,
			MSP_SET_RAW_GPS = 201,
			MSP_COMP_GPS = 107,
			MSP_ATTITUDE = 108,
			MSP_ALTITUDE = 109,
			MSP_ANALOG = 110,
			MSP_RC_TUNING = 111,
			MSP_SET_RC_TUNING = 204,
			MSP_PID = 112,
			MSP_SET_PID = 202,
			MSP_BOX = 113,
			MSP_SET_BOX = 203,
			MSP_MISC = 114,
			MSP_SET_MISC = 207,
			MSP_MOTOR_PINS = 115,
			MSP_BOXNAMES = 116,
			MSP_PIDNAMES = 117,
			MSP_WP = 118,
			MSP_SET_WP = 209,
			MSP_BOXIDS = 119,
			MSP_SERVO_CONF = 120,
			MSP_SET_SERVO_CONF = 212,
			MSP_ACC_CALIBRATION = 205,
			MSP_MAG_CALIBRATION = 206,
			MSP_RESET_CONF = 208,
			MSP_SELECT_SETTING = 210,
			MSP_SET_HEAD = 211,
			MSP_BIND = 240,
			MSP_EEPROM_WRITE = 250
		};
		
		MSP();
		
		void writeMSPData(MSP_COMMAND command, uint16_t data[12], uint8_t length);
		MSP_COMMAND readMSPData(uint16_t data[12]);
		
	private:
		
		uint8_t  read8();
		uint16_t read16();
		uint32_t read32();
		
		uint8_t checksum;
		char buffer[20];
		char buffer_2[20];
};

#endif // MSP_H
