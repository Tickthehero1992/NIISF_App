#include "sensor_data.h"
#include <iostream>
#define text_x 40
#define text_y 25
#define y_down_name 5
#define x_right_name 10
BOOL sensor_data::init_sensor(HINSTANCE hInstance, HWND hWnd, NAME_TYPE NAME, int id, int x, int y, int windth, int height)
{

	TYPER(NAME); //определяем тип и размерность показаний датчика на этапе инициализации
	NAME_sensor = NAME_sensor.append(" # "+to_string(id)+": "); //приводим имя датчика к строке чтения
	
	sensor_data::ID = id; //инициализируем ид датчика
	wstring Name_sens(NAME_sensor.begin(), NAME_sensor.end()); // создаем строки для окон WinApi с именами
	wstring Type_sens(type.begin(), type.end());
	/* создаем два окна для названия датчика и размерности*/
	CreateWindowEx(WS_EX_APPWINDOW,L"name_sensor", Name_sens.c_str(), WS_DISABLED|WS_CHILD| WS_VISIBLE , x, y, text_x , text_y, hWnd, NULL, hInstance, 0); //create sensor name
	CreateWindowEx(WS_EX_APPWINDOW,L"name_sensor", Type_sens.c_str(), WS_DISABLED | WS_CHILD | WS_VISIBLE , x+windth + text_x + x_right_name, y, text_x, text_y, hWnd, NULL, hInstance, 0); // create sensor type
	
	/*создаем поле для отображение данных*/
	sensor_data::sensor = CreateWindowEx(WS_EX_APPWINDOW, L"sensor pole", NULL, WS_DISABLED | WS_EX_CLIENTEDGE | WS_CHILD | WS_VISIBLE, x+text_x, y-y_down_name, windth, height, hWnd, NULL, hInstance, 0); // create sensor data pole
	ShowWindow(sensor, SW_SHOW);
	/*если создать его не получается выводим ошибку*/
	if (!sensor_data::sensor)
	{
		MessageBox(NULL,
			_T("Ошибка создания окна для датчика"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		return false;
	}
		return true;
}

/*
Типизация датчика по имени из перечисленных:
PRESSURE = 1,
TEMPERATURE = 2,
VOLTAGE = 3,
CURRENT = 4,
FREQUENCY = 5

после определения типа датчика
указывается его имя и
измеряемая величина

*/
void sensor_data::TYPER(NAME_TYPE NAME)
{
	switch (NAME)
	{
	case(PRESSURE):
		sensor_data::NAME_sensor = "P";
		sensor_data::type = "MPa ";
		break;
	case (TEMPERATURE):
		sensor_data::NAME_sensor = "T";
		sensor_data::type = "oC ";
		break;
	case (VOLTAGE):
		sensor_data::NAME_sensor = "V";
		sensor_data::type = "V ";
		break;			
	case (CURRENT):
		sensor_data::NAME_sensor = "C";
		sensor_data::type = "A ";
		break;
	case (FREQUENCY):
		sensor_data::NAME_sensor = "F";
		sensor_data::type = "HZ ";
		break;
	case (HUMIDITY):
		sensor_data::NAME_sensor = "f";
		sensor_data::type = "g/m^3 ";
		break;
	case (FLOW):
		sensor_data::NAME_sensor = "R";
		sensor_data::type = "l/min ";
		break;
	}
}

/*
Получение данных для датчика
*/

void sensor_data::data_put(float data)
{
	data_from_sensor = data;
}

LPCTSTR sensor_data::get_data()
{
	PAINTSTRUCT ps;
	HDC hdc;

	
	TCHAR temp[1024];
	_stprintf_s(temp, sizeof(temp) / sizeof(TCHAR), L"%f", sensor_data::data_from_sensor);
	
	//SetWindowText(sensor, STR.c_str());
	//TextOut(hdc, 0, 0, STR.c_str(),STR.length() );
	
	//InvalidateRect(sensor, 0, true);
	
	return temp;
}
