#include "PCHVx.h"

int32_t ConverterBytes(int32_t BYTES)
{
	return (BYTES >> 16) | ((BYTES & 0xFFFF)<<16);
}

void PCHVx::setKlemms(ParametrsKlemmPCHV Kl53, ParametrsKlemmPCHV Kl60)
{
	Klemm53 = Kl53;
	Klemm60 = Kl60;
}

void PCHVx::setTask(PCHVTaskParams* T)
{
	Task = *T;

}

void PCHVx::setPI(PIRegulator PI)
{
	Regulator = PI;
}

ModbusError PCHVx::SendData()
{

	build_message_modbus  Message;
	
	//Message.Create_message(address, _MODBUS_FUNC16, (uint16_t*)&Task.MinimumBar, PCHVRegMinimumBar, 2);
	//Message.Create_message(address, _MODBUS_FUNC16, (uint16_t*)&Task.MaximumBar, PCHVRegMaximumBar,2);
	
	Message.Create_message(address, _MODBUS_FUNC06, (uint16_t*)&Task.ProcentBar, PCHVRegPredefinedTask);



	//Message.Create_message(address, _MODBUS_FUNC06, (uint16_t*)&Task.ProcentBar, PCHVRegPredefinedTask, 5);
	/*Message.Create_message(address, _MODBUS_FUNC06, (uint16_t*)&Task.SpeedHz, PCHVRegFreqTask);
	Message.Create_message(address, _MODBUS_FUNC06, (uint16_t*)&Task.Source1, PCHVRegSourceTask1);
	Message.Create_message(address, _MODBUS_FUNC06, (uint16_t*)&Task.Source2, PCHVRegSourceTask2);
	Message.Create_message(address, _MODBUS_FUNC06, (uint16_t*)&Task.Source3, PCHVRegSourceTask3);*/
	return MODBUS_ERROR_OK;
}

void PCHVx::start()
{
	build_message_modbus  Message;
	int _Data_ = PCHVStart;
	uint16_t* datas = (uint16_t*)&_Data_;
	Message.Create_message(address, _MODBUS_FUNC06, datas, PCHVRegStart);
}

void PCHVx::stop()
{
	
		build_message_modbus  Message;
		int _Data_ = PCHVStop;
		uint16_t* datas = (uint16_t*)&_Data_;
		Message.Create_message(address, _MODBUS_FUNC06, datas, PCHVRegStart);
	

}