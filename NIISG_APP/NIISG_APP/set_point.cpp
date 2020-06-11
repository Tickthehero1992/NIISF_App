#include "set_point.h"
#define text_x 100
#define text_y 150
#define x_right_name 10
#define button_size_x 70
#define button_size_y 30

BOOL set_point::init_set_point(HINSTANCE hInstance, HWND hWnd, NAME_TYPE NAME, int id, int x, int y, int windth,  int height )
{
	TYPER(NAME);
	Name_object = Name_object.append(" Object # "+ to_string(id)+": ");
	set_point::ID = id+1;
	wstring Name_sens(Name_object.begin(), Name_object.end()); // создаем строки для окон WinApi с именами
	wstring Type_sens(type_object.begin(), type_object.end());

	/* создаем два окна для названия датчика и размерности*/
	CreateWindowEx(WS_EX_APPWINDOW, L"name_sensor", Name_sens.c_str(), WS_DISABLED | WS_CHILD | WS_VISIBLE, x, y-5, text_x, text_y, hWnd, NULL, hInstance, 0); //create sensor name

	set_point::set_point=CreateWindowEx(WS_EX_APPWINDOW, L"edit", L"0.0000", WS_CHILD | WS_VISIBLE|WS_BORDER| ES_CENTER, x + text_x , y-10, text_x, button_size_y, hWnd, (HMENU)(set_point::ID), hInstance, 0);

	CreateWindowEx(WS_EX_APPWINDOW, L"name_sensor", Type_sens.c_str(), WS_DISABLED | WS_CHILD | WS_VISIBLE, x + windth + text_x-x_right_name, y-5, text_x, text_y, hWnd, NULL, hInstance, 0); // create sensor type

	set_point::button=CreateWindowEx(WS_EX_APPWINDOW, L"BUTTON", L"Send", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, x + windth + text_x + x_right_name+20, y-10, button_size_x, button_size_y, hWnd, (HMENU)set_point::ID, hInstance, 0);
	return true;
}




void set_point::TYPER(NAME_TYPE NAME)
{
	switch (NAME)
	{
	case(PRESSURE):
		set_point::Name_object = "P";
		set_point::type_object = "MPa ";
		break;
	case (TEMPERATURE):
		set_point::Name_object = "T";
		set_point::type_object = "oC ";
		break;
	case (VOLTAGE):
		set_point::Name_object = "V";
		set_point::type_object = "V ";
		break;
	case (CURRENT):
		set_point::Name_object = "C";
		set_point::type_object = "A ";
		break;
	case (FREQUENCY):
		set_point::Name_object = "F";
		set_point::type_object = "HZ ";
		break;
	}
}