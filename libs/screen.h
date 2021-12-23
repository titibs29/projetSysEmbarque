#include <string.h>
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

#pragma once


void screenSendCommand(const char* cmd);

void screenInit();

void screenSetTemp(double temp);

void screenSetTemp(int temp);

void screenSetPwr(double pwr);

void screenSetLatitude(int lat);

void screenSetLongitude(int lon);

void screenSetPosition(double lat,double lon);

void screenSetSignal(int sig);

int screenStatus();

void screenClose();