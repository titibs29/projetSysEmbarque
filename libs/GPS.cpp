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


void GPS_location_GPGGA(char *lat, char *lng)
{
	int serial_port;
	int i = 0, k = 0;
	char data, buff[100] = "", NMEA_code[3] = "", NMEA_prefixe[3] = "", NMEATRAME[100] = "";
	string NMEA_code_s = "", buff_s;
	unsigned char IsitNMEAstring = 0;
	int NMEA_index = 0;
	unsigned char is_NMEA_received_completely = 0;

	if ((serial_port = serialOpen("/dev/ttyS0", 9600)) < 0) fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));

	if (wiringPiSetupGpio() == -1) fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));

	int c = 0;
	char character[70] = "$GPGGA,123519,50.449574,N,003.894473,E,1,08,0.9,545.4,M,46.9,M, , *42";

	while (is_NMEA_received_completely != 1)
	{
		bool vrai = true;
		if (/*serialDataAvail(serial_port)*/ vrai)  //check for any data available on serial port
		{
			//data = serialGetchar(serial_port);//character[c];
			data = character[c];
			c++;
			if (data == '$')
			{
				IsitNMEAstring = 0;
				//NMEA_index = 0;
				cout << "le character $ est detecte !!" << endl;
			}
			else if (IsitNMEAstring == 1)
			{
				//buff[NMEA_index] = data;
				buff_s += data;
				cout << "Le buffeur d'index " << NMEA_index << " est : " << buff[NMEA_index] << " prenant la valeur de data : " << data << endl;
				//NMEA_index++;
				if (data == '*')
					is_NMEA_received_completely = 1;
			}
			else if (NMEA_prefixe[0] == 'G' && NMEA_prefixe[1] == 'G' && NMEA_prefixe[2] == 'A') //NMEA_code[0] == 'R' && NMEA_code[1] == 'M' && NMEA_code[2] == 'C'
			{
				IsitNMEAstring = 1;
				for (i = 0; i < 3; i++)
				{
					NMEA_code[i] = NMEA_prefixe[i];
					NMEA_prefixe[i] = '0';
				}
				for (i = 0; i < 3; i++) NMEA_code_s += NMEA_code[i];
			}
			else
			{
				NMEA_prefixe[0] = NMEA_prefixe[1];
				NMEA_prefixe[1] = NMEA_prefixe[2];
				NMEA_prefixe[2] = data;

			}
		}
		if (is_NMEA_received_completely == 1)
		{
			//"123519,50.449574,N,003.894473,E,1,08,0.9,545.4,M,46.9,M, , *42"
			cout << NMEA_code_s << " : " << buff_s << endl;
			strcpy(lat, (buff_s.substr(7, 9)).c_str());
			cout << lat << endl;
			strcpy(lng, (buff_s.substr(19, 10)).c_str());
			cout << lng << endl;

			c = 0;
			NMEA_index = 0;
		}
	}
	is_NMEA_received_completely = 0;
}

float StringToInt(string in)
{
	return atof(in.c_str());
}

string ChartoString(char parameter[])
{
	string s = "";

	for (int i = 0; i < sizeof(parameter) - 1; i++) s += parameter[i];

	return s;
}

void StringtoChar(string parameter, char* char_p)
{
	// declaring character array : p
	/*
	char p[parameter.length];
	int i;
	for (i = 0; i < strlen(p); i++)
	{
		p[i] = parameter[i];
		//cout << p[i];
	}
	*/

	strcpy(char_p, parameter.c_str());
}