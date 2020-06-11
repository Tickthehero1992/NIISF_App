#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <sstream>

#define x_size 100
#define y_size 30
using namespace std;

typedef enum
{
	PRESSURE = 1,
	TEMPERATURE = 2,
	VOLTAGE = 3,
	CURRENT = 4,
	FREQUENCY = 5,
	HUMIDITY = 6,
	FLOW = 7 
} NAME_TYPE;

typedef struct
{
	NAME_TYPE Name;
	string type;
} SENSOR;

class sensor_data 
{
	string NAME_sensor;
	string type;
	int ID;
	void TYPER(NAME_TYPE);
	float data_from_sensor=0;
public:
	HWND sensor;
	BOOL init_sensor(HINSTANCE hInstance, HWND hWnd, NAME_TYPE NAME, int id, int x, int y, int windth = x_size, int height = y_size);
	LPCTSTR get_data();
	void data_put(float data);
};

