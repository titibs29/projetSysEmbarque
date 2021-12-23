										///////////CODE RTC/////////

#define _CRT_SECURE_NO_WARNINGS

#include "rtc.h"


#define slave_Add 0b1101000 //0x68
using namespace std;



int slave_Address;

					//Initialisation de la librairie pour avoir l'heure et les dates actuelles//
time_t t = time(NULL);
tm* tPtr = localtime(&t);
					//Initialisation de la librairie pour avoir l'heure et les dates actuelles//
/* int main(void)

{
	

	wiringPiSetupGpio();
	slave_Address = wiringPiI2CSetup(slave_Add);

	int heure = 0, minute = 0, seconde = 0, day = 0, date = 0, month = 0, year = 0;

	RTC_Init(seconde, minute, heure, day, date, month, year); //Initialisation aux valeurs envoyées (valeurs actuelles)

	while (true)
	{
		
		int sec = RTC_read(slave_Address, 0); //sec
		int min = RTC_read(slave_Address, 1); //min
		int h = RTC_read(slave_Address, 2); //heures 
		int day = RTC_read(slave_Address, 3); //Day
		int date = RTC_read(slave_Address, 4); //Date
		int month = RTC_read(slave_Address, 5); //Month
		int year = RTC_read(slave_Address, 6); // Year

		cout << give_day_of_week(transfoDCB_To_Dec(day)) << " " << transfoDCB_To_Dec(date) << " " << give_month_of_year(transfoDCB_To_Dec(month)) << " " <<20<<transfoDCB_To_Dec(year) << "~~" << transfoDCB_To_Dec(h) << ":" << transfoDCB_To_Dec(min) << ":" << transfoDCB_To_Dec(sec) << ":" << endl;
		delay(1000);
	}
	return 0;
}
 */

string give_day_of_week(int day) {
	switch (day) {
	case 1: return "LUN";
	case 2: return "MAR";
	case 3: return "MER";
	case 4: return "JEU";
	case 5: return "VEN";
	case 6: return "SAM";
	case 7: return "DIM";
	default: return "   ";
	}
}
string give_month_of_year(int month) {
	switch (month)
	{
	case 1: return "Jan";
	case 2: return "Feb";
	case 3: return "Mar";
	case 4: return "Apr";
	case 5: return "May";
	case 6: return "June";
	case 7: return "Jul";
	case 8: return "Aug";
	case 9: return "Sept";
	case 10: return "Oct";
	case 11: return "Nov";
	case 12: return "Dec";
	default: return "   ";
	}
}
//Initialisation et fonction de vérification
void RTC_Init(int secondes, int minutes, int heures, int day, int date, int month, int year)
{
	if (heures >= 23)
	{
		heures = heures % 23;
	}
	if (minutes >= 60)
	{
		minutes = minutes % 60;
	}
	if (secondes >= 60)
	{
		secondes = secondes % 60;
	}
	if (day >= 7)
	{
		day = day % 7;
	}
	if (date >= 31)
	{
		date = date % 31;
	}
	if (month >= 12)
	{
		month = month % 12;
	}
	RTC_Send(slave_Address, 0, transfo_Dec_To_DCB(tPtr->tm_sec)); //Seconde
	RTC_Send(slave_Address, 1, transfo_Dec_To_DCB(tPtr->tm_min)); //Minute
	RTC_Send(slave_Address, 2, transfo_Dec_To_DCB(tPtr->tm_hour)); //hour
	RTC_Send(slave_Address, 3, transfo_Dec_To_DCB(tPtr->tm_wday)); //Day of week
	RTC_Send(slave_Address, 4, transfo_Dec_To_DCB(tPtr->tm_mday)); //Date of month 
	RTC_Send(slave_Address, 5, transfo_Dec_To_DCB(tPtr->tm_mon) + 1); //Month
	RTC_Send(slave_Address, 6, transfo_Dec_To_DCB(21)); //year
}

int RTC_read(int address, int reg)
{
	int read = wiringPiI2CReadReg8(address, reg);
	return read;
}

void RTC_Send(int address, int regis, int data)
{
	wiringPiI2CWriteReg8(address, regis, data);
}

int transfoDCB_To_Dec(int data)
{
	int unit, ten;
	unit = data & 0b00001111;
	ten = data >> 4 & 0b00001111;
	return ten * 10 + unit;
}

int transfo_Dec_To_DCB(int number)
{
	int unit, ten, DCB = 0;
	unit = number % 10; //Récupération de l'unité
	ten = (number - unit) / 10; //Récupération de la dizaine
	DCB = DCB + ten; //On ajoute la dizaine ...
	DCB = DCB << 4; //..On décale pour la mettre à droite
	DCB = DCB + unit; // On ajoute l'unité
	return DCB;
}


