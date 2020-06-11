#include "SensorIFaceConverter.h"

void SensorIFaceConverter::get_data()
{
	build_message_modbus Message;
	Message.Create_message(address, _MODBUS_FUNC04,0x00, StateRegStartMB110, sensor_num);
	for (uint8_t i = 0; i < sensor_num; i++)
	{
		SensorOnWire[i].State = Message.Parsed_message->response0304.values[i];
	}
	Message.Create_message(address, _MODBUS_FUNC04, 0x00, DataRegStartMB110, sensor_num*3);
	int k = 0;
	for (uint8_t i = 0; i < sensor_num; i++)
	{
		SensorOnWire[i].DataFromSensor.DataInt[0] = Message.Parsed_message->response0304.values[i+k];
		SensorOnWire[i].DataFromSensor.DataInt[1] = Message.Parsed_message->response0304.values[i+1+k];
		SensorOnWire[i].Time = Message.Parsed_message->response0304.values[i + 2+k];
		k += 2;
	}

}