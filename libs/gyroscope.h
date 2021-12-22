#include <wiringPiI2C.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>


#pragma once

void MPU6050_Init();

short read_raw_data(int addr);

void ms_delay(int val);

void traitementGyro();

int mainGyroscope();

void ms_delay(int val);

