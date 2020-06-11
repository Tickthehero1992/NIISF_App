// NIISG_APP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "main.h"
#include <fstream>
int main()
{
    std::string A;
    std::string speed;
    std::string data;
    std::string parity;
    std::string stop;
    //std::cout << "Hello World!\n";
    std::ifstream setups("setups.txt");
    if (setups.is_open())
    {

        std::getline(setups, A);
        std::getline(setups, speed);
        std::getline(setups, data);
        std::getline(setups, parity);
        std::getline(setups, stop);


    }
    std::cout << "Com port:"<< A <<" Speed "<<speed <<" Data "<<data 
        <<" Parity "<<parity<< " Stop "<<stop<< std::endl;
    int Speed = atoi(speed.c_str());
    int DataBits = atoi(data.c_str());
    int Parity = atoi(parity.c_str());
    int StopBits = atoi(stop.c_str());
    LPCTSTR B = (LPCTSTR)A.c_str();
    init_com(B, Speed, DataBits, Parity, StopBits);
    Init_Modbus(); 
    PCHVx PCHV1(0x02);//3
    //PCHVTaskParams T = { ConverterBytes(1), ConverterBytes(1000),1900,10,3,1,1,2,0 };
    //PCHV1.setTask(&T);
    PCHV1.SendData();
    PCHV1.start();

    
    /*
    SensorIFaceConverter Converter1(0x10);
    Converter1.get_data();*/

    //regulator REG1(0x04);
    //regulator REG2(0x05);
    //regulator REG3(0x06);
    //REG1.set_state(0);
    //REG2.set_state(100);
    //REG3.set_state(0);
    std::ofstream out;
    out.open("output.csv");
    SYSTEMTIME st;
    GetSystemTime(&st);
    out << "Hour: "<<st.wHour<<" Minuts "<< st.wMinute <<" Seconds: "<< st.wSecond << endl;
    out.close();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
