#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <ctime>

#include "libs/screen.h"
#include "libs/SMS.h"
#include "libs/Convertisseur_puissance.h"
#include "libs/Temperature.h"
#include "libs/gyroscope.h"
#include "libs/rtc.h"
#include "libs/stepper.h"
#include "libs/GPS.h"

// Define du convertisseur
#define ADDR_I2C 0x68 // Adresse en hexa de la communication I2C
#define pinBase 100
#define Taux_echantillonnage 0
#define Gain 0

// Define du stepper
#define CLK 27
#define DIR 26
#define BUTTON 16

// système de containers, permet d'activer et desactiver les modules correspondants
#define gyrosActive true
#define gpsActive false
#define rtcActive false
#define magnetoActive false
#define gsmActive false
#define screenActive false
#define tempActive false
#define convActive false
#define stepActive false

int main(void)
{
    wiringPiSetup();

    // variables
    // gyroscope
    float gx = 0, gy = 0, gz = 0;
    float *p_gx = &gx;
    float *p_gy = &gy;
    float *p_gz = &gz;

    // stepper
    int rise_time = 1, time_between_steps = 1;
    float lat_heh = 1.352083; // MONS : 50.454241;
    int ctr = 0;              // unused
    time_t t = time(NULL);
    tm *tPtr = localtime(&t);

    // gsm
    bool envoiMessage = true;
    char numero[20] = "\"+32494801130\"";
    char message[200] = "Votre Message ici.";

    // Init Gyro
    if (gyrosActive)
    {
        MPU6050_Init();
    }

    if (gpsActive)
    {
    }

    if (rtcActive)
    {
        wiringPiSetupGpio();
        slave_Address = wiringPiI2CSetup(slave_Add);

        int heure = 0, minute = 0, seconde = 0, day = 0, date = 0, month = 0, year = 0;

        RTC_Init(seconde, minute, heure, day, date, month, year); // Initialisation aux valeurs envoyées (valeurs actuelles)
    }

    if (magnetoActive)
    {
    }

    if (gsmActive)
    {
    }

    if (screenActive)
    {
        screenInit();
    }

    // Init Capteur_Température
    if (tempActive)
    {
        max31855Setup(200, 0);
    }

    // Init Convertisseur_température
    if (convActive)
    {
        mcp3422Setup(pinBase, ADDR_I2C, Taux_echantillonnage, Gain);
    }

    if (stepActive)
    {
        wiringPiSetupGpio();

        pinMode(CLK, OUTPUT);
        pinMode(DIR, OUTPUT);
        pinMode(BUTTON, INPUT);

        step_day_light(t, tPtr, lat_heh, rise_time, time_between_steps);
    }

    // INIT

    while (1)
    {

        if (gyrosActive)
        {
            traitementGyro(p_gx, p_gy, p_gz);
            printf("x= %.2f, y= %.2f, z= %.2f", gx, gy, gz);
        }

        if (gpsActive)
        {
        }

        if (rtcActive)
        {
            int sec = RTC_read(slave_Address, 0);   // sec
            int min = RTC_read(slave_Address, 1);   // min
            int h = RTC_read(slave_Address, 2);     // heures
            int day = RTC_read(slave_Address, 3);   // Day
            int date = RTC_read(slave_Address, 4);  // Date
            int month = RTC_read(slave_Address, 5); // Month
            int year = RTC_read(slave_Address, 6);  // Year

            cout << give_day_of_week(transfoDCB_To_Dec(day)) << " " << transfoDCB_To_Dec(date) << " " << give_month_of_year(transfoDCB_To_Dec(month)) << " " << 20 << transfoDCB_To_Dec(year) << "~~" << transfoDCB_To_Dec(h) << ":" << transfoDCB_To_Dec(min) << ":" << transfoDCB_To_Dec(sec) << ":" << endl;
            delay(1000);
        }

        if (magnetoActive)
        {
        }

        if (gsmActive)
        {
            if (envoiMessage)
            {
                envoiMessage = false;
            }

            SendSMS(numero, message);
        }

        if (tempActive)
        {
        }

        if (convActive)
        {
        }
        if (stepActive)
        {
            int temp_rise_time = rise_time; // garder en permanence en mémoire le rise time calculé au power on.
            do_steps(t, tPtr, lat_heh, rise_time, temp_rise_time, time_between_steps);
        }

        if (screenActive)
        {

            // code de démonstration, veuillez remplacer les chiffres par les variables
            screenSetTemp(24.5);

            screenSetPwr(245.0);

            screenSetPosition(50.460860, 3.957098);

            screenSetSignal(2);
        }
    }
    return 0;
}
