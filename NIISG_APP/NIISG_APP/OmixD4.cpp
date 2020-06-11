#include "OmixD4.h"

OmixD4Parametres OmixD4::getParams()
{
	build_message_modbus Message;
	Message.Create_message(Address, _MODBUS_FUNC04, NULL, OmixD4ParamRegistStart, OmixD4NumberOfResiters);
	OmixD4Parametres* params = (OmixD4Parametres*)Message.Parsed_message->response0304.values;
	Params = *params;
	return Params;
}
