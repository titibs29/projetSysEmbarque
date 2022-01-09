#define _CRT_SECURE_NO_WARNINGS //stop warning boring when i run code
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "unistd.h"
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;


void GPS_location_GPGGA(char *lat, char *lng);

float StringToInt(string in);

string ChartoString(char parameter[]);

void StringtoChar(string parameter, char* char_p);
