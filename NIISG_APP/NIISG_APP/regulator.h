#include "build_message_modbus.h"
#define regulator_address_default 0x01
#define regulator_register_to_address 0x0000
#define regulator_register_to_state 0x0001

typedef enum
{
	REGULATOR_OFF=0,
	REGULATOR_ON=1,
	REGULATOR_ERROR=2
}
REGULATOR_STATE;
#pragma once
class regulator
{
private:
	uint8_t address;
	uint16_t state;
public:
	regulator(uint8_t addr)
	{
		address = addr;
		state = get_state();
	}
	uint16_t get_state();
	uint8_t get_address();
	uint16_t set_state(uint16_t);
	//void set_address(uint16_t address)
};

