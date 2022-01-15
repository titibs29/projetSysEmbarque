#include <wiringPiI2C.h>
#include <chrono>
#include <string>

void RTC_Send(int address, int regis, int data);                                              // Envoi de valeur dans la RTC
int RTC_read(int address, int reg);                                                           // Lecture de ces valeurs
void RTC_Init(int secondes, int minutes, int heures, int day, int date, int month, int year); // Utilisation de RTC_Send pour initialiser à 0
std::string give_day_of_week(int day);
std::string give_month_of_year(int month);

int transfo_Dec_To_DCB(int number); // Ecriture dans la RTC --> Envoi en format DCB
int transfoDCB_To_Dec(int number);  // Lecture --> Conversion de DCB en decimal

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