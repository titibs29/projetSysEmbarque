#include <cmath>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <string>

void RTC_Send(int address, int regis, int data);                                              // Envoi de valeur dans la RTC
int RTC_read(int address, int reg);                                                           // Lecture de ces valeurs
void RTC_Init(int secondes, int minutes, int heures, int day, int date, int month, int year); // Utilisation de RTC_Send pour initialiser à 0
std::string give_day_of_week(int day);
std::string give_month_of_year(int month);

int transfo_Dec_To_DCB(int number); // Ecriture dans la RTC --> Envoi en format DCB
int transfoDCB_To_Dec(int number);  // Lecture --> Conversion de DCB en decimal