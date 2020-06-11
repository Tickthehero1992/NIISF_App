#include "build_message_modbus.h"


#define OmixD4NumberOfResiters 0x37
#define OmixD4ParamRegistStart 0x22

#pragma pack(push,1)
typedef struct
{
	uint16_t LinA_B;
	uint16_t LinB_C;
	uint16_t LinA_C;
	uint16_t PhaseA;
	uint16_t PhaseB;
	uint16_t PhaseC;
	uint16_t CurrentA;
	uint16_t CurrentB;
	uint16_t CurrentC;
	uint16_t FrequencyCurrent;
	uint16_t SumOfActivePower;
	uint32_t SumOfReactivePower;
	uint16_t SumKoefOfPower;
	uint16_t ActivePowerA;
	uint16_t ActivePowerB;
	uint16_t ActivePowerC;
	uint16_t ReactivePowerA;
	uint16_t ReactivePowerB;
	uint16_t ReactivePowerC;
	uint16_t PowerA;
	uint16_t PowerB;
	uint16_t PowerC;
	uint16_t KoefPowerA;
	uint16_t KoefPowerB;
	uint16_t KoefPowerC;
	uint16_t AverageVoltage;
	uint16_t AverageCurrent;
	uint16_t MaximumVoltageA_B;
	uint16_t MaximumVoltageB_C;
	uint16_t MaximumVoltageA_C;
	uint16_t MinimumVoltageA;
	uint16_t MinimumVoltageB;
	uint16_t MinimumVoltageC;
	uint16_t MaximumCurrentA;
	uint16_t MaximumCurrentB;
	uint16_t MaximumCurrentC;
	uint16_t MinimumCurrentA;
	uint16_t MinimumCurrentB;
	uint16_t MinimumCurrentC;
	uint32_t PositiveActiveEnergy;
	uint32_t NegativeActiveEnergy;
	uint32_t PositiveReactiveEnergy;
	uint32_t NegativeReactiveEnergy;
	uint16_t CRC;
} OmixD4Parametres;
#pragma push(pop)

#pragma once
class OmixD4
{
private:
	uint8_t Address;
	OmixD4Parametres Params;
public:
	OmixD4(uint8_t addres)
	{
		Address = addres;
	};
	OmixD4Parametres getParams();
};

