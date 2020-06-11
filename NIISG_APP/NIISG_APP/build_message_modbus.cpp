#include "build_message_modbus.h"

static ModbusMaster mstatus;
static HANDLE hSerialport;
static const uint8_t* txFramePtr;

int init_com(LPCTSTR A, int Speed, int DataBits, int Parity, int StopBits)
{
    
    LPCTSTR portName = L"COM2";
    hSerialport = ::CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    //If some error occured
    if (hSerialport == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) std::cout << "This serial port doesn't exist\n";
        std::cout << "Some other shit occured\n";

    }
    COMMTIMEOUTS comTimeOut;

    comTimeOut.ReadIntervalTimeout = 100;
    comTimeOut.ReadTotalTimeoutMultiplier = 1;
    comTimeOut.ReadTotalTimeoutConstant = 1;
    comTimeOut.WriteTotalTimeoutMultiplier = 3;
    comTimeOut.WriteTotalTimeoutConstant = 2;
    SetCommTimeouts(hSerialport, &comTimeOut);
    //Connection setting up
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerialport, &dcbSerialParams))
    {
        std::cout << "getting state error\n";
    }
    switch (Speed)
    {
    case (9600):
        dcbSerialParams.BaudRate = CBR_9600;
        break;
    case (19200):
        dcbSerialParams.BaudRate = CBR_19200;
        break;

    case (38400):
        dcbSerialParams.BaudRate = CBR_38400;
        break;

    case (57600):
        dcbSerialParams.BaudRate = CBR_57600;
        break;

    case (115200):
        dcbSerialParams.BaudRate = CBR_115200;
        break;
    }
    
    dcbSerialParams.ByteSize = DataBits;
    switch (StopBits)
    {
    case 2:
            dcbSerialParams.StopBits = TWOSTOPBITS;
            break;
    case 0:
        dcbSerialParams.StopBits = ONE5STOPBITS;
        break;
    case 1:
        dcbSerialParams.StopBits = ONESTOPBIT;
        break;
     }
    
    switch (Parity)
    {
    case (0):
        dcbSerialParams.Parity = NOPARITY;
        break;
    case (1):
        dcbSerialParams.Parity = ODDPARITY;
        break;
    case(2):
        dcbSerialParams.Parity = EVENPARITY;
        break;
    }
    
    if (!SetCommState(hSerialport, &dcbSerialParams))
    {
        std::cout << "error setting serial port state\n";
    }
    //Query string
       // Main message loop:
  /* 
    char data[] = "Hello from C++\n";
    DWORD dwSize = sizeof(data);   // string length
    DWORD dwBytesWritten;    // transmitted bytes amount
    //Sending
    while (true)
    {
        BOOL iRet = WriteFile(hSerialport, data, dwSize, &dwBytesWritten, NULL);
        if (!iRet) std::cout << "Some shit occured\n";
        std::cout << dwSize << " Bytes in string. " << dwBytesWritten << " Bytes sended. " << std::endl;
        Sleep(1000);
    }
*/
    return 0;
}




ModbusError Init_Modbus()
{
    txFramePtr = (const uint8_t*)calloc(_MODBUS_FRAME_MAX_LENGTH, sizeof(uint8_t));
    return modbusMasterInit(&mstatus);
}

void DeInit_Modbus()
{
    free((void*)txFramePtr);
}


ModbusError build_message_modbus::Create_message(uint8_t slaveAddr, uint8_t func_name, uint16_t* txData, uint16_t startRegAddr, uint16_t regCount)
{
    switch (func_name)
    {
        case (_MODBUS_FUNC01):
        case (_MODBUS_FUNC02):
            modbusBuildRequest0102(&mstatus, func_name, slaveAddr, startRegAddr, regCount);
            break;

        case (_MODBUS_FUNC03):
        case (_MODBUS_FUNC04):
            modbusBuildRequest0304(&mstatus, func_name, slaveAddr, startRegAddr, regCount);
            break;

        case (_MODBUS_FUNC05):
            modbusBuildRequest05(&mstatus, slaveAddr, startRegAddr, txData[0]);
            break;

        case (_MODBUS_FUNC06):
            modbusBuildRequest06(&mstatus, slaveAddr, startRegAddr, txData[0]);
            break;

        case (_MODBUS_FUNC15):
            modbusBuildRequest15(&mstatus, slaveAddr, startRegAddr, regCount, (uint8_t*)txData);
            break;

        case (_MODBUS_FUNC16):
            modbusBuildRequest16(&mstatus, slaveAddr, startRegAddr, regCount, txData);
            break;

        default: return MODBUS_ERROR_BUILD;
    }

    if (!WriteFile(hSerialport, mstatus.request.frame, mstatus.request.length, NULL, NULL)) goto _ERROR;
    if (!ReadFile(hSerialport, (LPVOID*)txFramePtr, _MODBUS_FRAME_MAX_LENGTH, (DWORD*)&mstatus.response.length, NULL)) goto _ERROR;
    mstatus.response.frame = txFramePtr;
    memcpy((void*)mstatus.response.frame, txFramePtr, mstatus.response.length);
    Parsed_message = (ModbusParser*)mstatus.response.frame;
    
    
    if (MODBUS_ERROR_OK != modbusParseResponse(&mstatus)) goto _ERROR;

    return MODBUS_ERROR_OK;

_ERROR:
    return MODBUS_ERROR_OTHER;
}