#include <string.h>
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

#pragma once

void MPU6050_Init();

short read_raw_data(int addr);

void ms_delay(int val);

void traitementGyro();

int mainGyroscope();