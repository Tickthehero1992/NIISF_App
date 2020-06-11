#include "build_message_modbus.h"



/**********************Setup Registers for PCHV********************************/
//Predefined setups 
#define PCHVRegChooseTask 0x08
#define PCHVRegPLKPower 0x32C7
#define PCHVRegPLKTask 0x34CF
#define PCHVRegSetNumber 0x63
#define PCHVRegSetChange 0x6D
#define PCHVRegSpinning 0x1003
//Setups for tasks
#define PCHVRegConfiguration 0x3E7
#define PCHVRegMoment 0X405
#define PCHVRegMinimumBar 0XBCB
#define PCHVRegMaximumBar 0XBD5
#define PCHVRegPredefinedTask 0XC1B
#define PCHVRegFreqTask 0xC25
#define PCHVRegSourceTask1 0XC4D
#define PCHVRegSourceTask2 0XC57
#define PCHVRegSourceTask3 0xC61
#define PCHVRegMaximumFrequency 0X102B
//Setups for Klemm 53
#define PCHVRegMinCurrent53 0X17E7
#define PCHVRegMaxCurrent53 0X17F1
#define PCHVRegScaleHighTask53 0X1805
#define PCHVRegScaleLowTask53 0x17FB
#define PCHVRegFilterPeriod53 0x180F
#define PCHVRegMode53 0X180D
//Setups for Klemm 60
#define PCHVRegMinCurrent60 0x184B
#define PCHVRegMaxCurrent60 0x1855
#define PCHVRegScaleHighTask60 0X185F
#define PCHVRegScaleLowTask60 0x1869
#define PCHVRegFilterPeriod60 0x1873
//Setups for Klemm 42
#define PCVHRegMode42 0x1AF3
#define PCHVRegAnalogOut42 0x1AFD
#define PCHVRegDigitalOut42 0x1B07
#define PCHVRegScaleMin42 0x1B11
#define PCHVRegScaleMax42 0x1B1B
//Setups for PI-regulator
#define PCHVRegSourcePI 0x1C1F
#define PCHVRegModePI 0x1C83 
#define PCHVRegAntireversPI 0x1C8D
#define PCHVRegSpeedPI 0x1C97
#define PCHVRegPIP  0x1CA1
#define PCHVRegPII 0x1CAB
#define PCHVRegKoefPI 0x1CD3
#define PCHVRegZonePI 0x1CDD
/******************************************************************************************/

/*********Constatns for main parametersfor Task******************************/
#define PCHVSetNumberConst 0x02
#define PCHVRegSpinningConst 0x00 //Spinning of driver only time arrow
#define PCHVModeTask 0x03 // mode of configuration, PI-mode
#define PCHVSpinMoment 0x02 //spin moment . avtomatic optimization of elictric power
#define PCHVMaxFreqConst 0x32 // frquency of invertor 50Hz
#define PCHVMode53Const 0x01 //mode for cl 53 is Current Mesuare 
#define PCHVProporKoefConst 0x01 //proportional koef of PI
#define PCHVIntKoefConst 0x08 // integral koef of PI

#define PCHVRegStart 0xC34F
#define PCHVStart  1<<6
#define PCHVStop 1<<7
/***************************************************************************/
int32_t ConverterBytes(int32_t);
#pragma pack(push,2)
typedef struct
{
	int32_t MinimumBar;
	int32_t MaximumBar;
	int16_t ProcentBar;
	uint16_t SpeedHz;
	uint16_t AccelerationProcent;
	int32_t PredefinedTask;
	uint16_t Source1;
	uint16_t Source2;
	uint16_t Source3;

}PCHVTaskParams;
#pragma push(pop)

#pragma pack(push,2)
typedef struct
{
	uint16_t MinimumCurrent;
	uint16_t MaximumCurrent;
	uint16_t ScopeMaximumTask;
	uint16_t ScopeMinimumTask;
	uint16_t FilterTime;
} ParametrsKlemmPCHV;
#pragma push(pop)

#pragma pack(push, 2)
typedef struct
{
	uint16_t ModePI;
	uint16_t SourcePI;
	uint16_t ProportionalKoef;//7-34
	uint16_t IntegramKoef;
}PIRegulator;
#pragma push(pop)


#pragma once
class PCHVx
{
private:
	uint8_t address;
	ParametrsKlemmPCHV Klemm53;
	ParametrsKlemmPCHV Klemm60;
	PIRegulator Regulator;
	PCHVTaskParams Task;

public:
	PCHVx(uint8_t addr)
	{
		build_message_modbus MessageInit;
		address = addr;
		/*
		int _Data_ = PCHVSetNumberConst;
	 	uint16_t* datas = (uint16_t*)&_Data_;
	
		if (MessageInit.Create_message(address, _MODBUS_FUNC06, datas, PCHVRegSetNumber, 0) != MODBUS_ERROR_OK) //number of sets
		{
		}
		_Data_ = 0x02;
		if (MessageInit.Create_message(address, _MODBUS_FUNC06, datas, PCHVRegSetChange, 0) != MODBUS_ERROR_OK) //number of sets
		{
		}
		_Data_ = PCHVRegSpinningConst;
		if (MessageInit.Create_message(address, _MODBUS_FUNC06, datas , PCHVRegSpinning, 0) != MODBUS_ERROR_OK) //spin direct
		{
		}
		_Data_ = PCHVModeTask;
		if (MessageInit.Create_message(address, _MODBUS_FUNC06, datas, PCHVRegConfiguration, 0) != MODBUS_ERROR_OK) // low power
		{
		}
		_Data_ = PCHVSpinMoment;
		if (MessageInit.Create_message(address, _MODBUS_FUNC06, datas, PCHVRegMoment, 0) != MODBUS_ERROR_OK) // Spin moment
		{
		}
		_Data_ = 0x01;
		if (MessageInit.Create_message(address, _MODBUS_FUNC06, datas, PCHVRegPLKPower, 0) != MODBUS_ERROR_OK) // Spin moment
			{
			}
		_Data_ = 0x11;
		if (MessageInit.Create_message(address, _MODBUS_FUNC06, datas, PCHVRegPLKTask) != MODBUS_ERROR_OK) // Spin moment
		{
		}
		_Data_ = 0x01;
		MessageInit.Create_message(address, _MODBUS_FUNC06, datas, PCHVRegChooseTask);*/
	
	}
	void setPI(PIRegulator);
	void setTask(PCHVTaskParams*);
	void setKlemms(ParametrsKlemmPCHV, ParametrsKlemmPCHV);
	void start();
	void stop();
	ModbusError SendData();
};

