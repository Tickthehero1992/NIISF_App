#include "build_message_modbus.h"

#define NUMBEROFSENSORS 0X08
#define DataRegStartMB110 0x120
#define StateRegStartMB110 0x118

#define SUCCEESSMESUARE 0x0000
#define WRONGMESUARE 0x00F0
#define DATANOTREADY 0x06F0
#define SENSOROFF 0x07F0
#define MESUAREHIGH 0x0AF0
#define MESUARELOW 0x0BF0
#define SENSORLOST 0x0DF0
#define CALLIBRATIONINCORRECT 0x0FF0

#pragma pack(push,1)
typedef struct
{
	uint16_t State;
	uint16_t Time;
	union
	{
		float DataFloat;
		uint16_t DataInt[2];

	} DataFromSensor;
}SensorState;
#pragma pack(pop)

#pragma once
class SensorIFaceConverter
{
private:
	uint8_t address;
	uint8_t sensor_num;
public:
	SensorIFaceConverter(uint8_t add, uint8_t sensors= NUMBEROFSENSORS)
	{
		address = add;
		sensor_num=sensors;

	};
	void get_data();
	uint8_t get_address()
	{
		return address;
	};
	SensorState SensorOnWire[NUMBEROFSENSORS];

};

