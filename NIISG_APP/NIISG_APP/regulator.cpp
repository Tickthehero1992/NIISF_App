#include "regulator.h"

/*void regulator::set_address(uint16_t addr)
{
    build_message_modbus Message_address;
    Message_address.Create_message(&addr, 0x06, address, regulator_register_to_address);
    address = addr;
}*/

uint16_t regulator::get_state()
{
    return set_state(state);
    //return REGULATOR_ON;
}

uint8_t regulator::get_address()
{
    return address;
}

uint16_t regulator::set_state(uint16_t StatePower)
{
    build_message_modbus Message_address;
    Message_address.Create_message(address, _MODBUS_FUNC06, (uint16_t*)StatePower, regulator_register_to_state);
    uint16_t NewState = Message_address.Parsed_message->response06.value;
    if (NewState != state) return 255;
    return state;
}

