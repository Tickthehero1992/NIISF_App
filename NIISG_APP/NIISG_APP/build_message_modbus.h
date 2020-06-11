#include <lightmodbus/lightmodbus.h>
#include <windows.h>
#include <iostream>
#include <string>
//#include "main.h"
using namespace std;

#define _MODBUS_FUNC01           0x01
#define _MODBUS_FUNC02           0x02
#define _MODBUS_FUNC03           0x03
#define _MODBUS_FUNC04           0x04
#define _MODBUS_FUNC05           0x05
#define _MODBUS_FUNC06           0x06
#define _MODBUS_FUNC15           0x0F
#define _MODBUS_FUNC16           0x10
#define _MODBUS_FRAME_MAX_LENGTH 256

int init_com(LPCTSTR A, int Speed, int DataBits, int Parity,  int StopBits);
ModbusError Init_Modbus();

typedef enum
{
	GET_DATA=0,
	SET_DATA=1
}DATA_ACT;

#pragma once
class build_message_modbus
{
public:
	ModbusError Create_message(uint8_t slaveAddr, uint8_t func_name, uint16_t* txData, uint16_t startRegAddr, uint16_t regCount = 0);
	ModbusParser* Parsed_message;
};

