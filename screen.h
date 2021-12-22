#include <string.h>
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

#pragma once

void sendCommand(const char* cmd);

void Init();

void setTemp(double temp);

void setTemp(int temp);

void setPwr(double pwr);

void setLatitude(int lat);

void setLongitude(int lon);

void setPosition(double lat,double lon);

void setSignal(int sig);

int status();

void close();