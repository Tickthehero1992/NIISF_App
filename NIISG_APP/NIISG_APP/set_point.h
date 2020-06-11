#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <vector>
#include <string>
#include "sensor_data.h"

#define x_size_set 100
#define y_size_set 30

using namespace std;
class set_point
{
private:
    
    void TYPER(NAME_TYPE);
    string Name_object;
    string type_object;
public:
    BOOL init_set_point(HINSTANCE hInstance, HWND hWnd, NAME_TYPE NAME, int id, int x, int y, int windth = x_size_set, int height = y_size_set);
    BOOL send_data();
    HWND button;
    HWND set_point;
    int ID;
    float data;

};

