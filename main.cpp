#include <iostream>
#include <wiringPi.h>
#include <chrono>
#include <mcp3422.h>
#include <max31855.h>

#include "libs/gyroscope.h"
#include "libs/Convertisseur_puissance.h"
#include "libs/screen.h"
#include "libs/SMS.h"
#include "libs/Temperature.h"
// #include "libs/rtc.h"

// Define du convertisseur
#define ADDR_I2C 0x68 // Adresse en hexa de la communication I2C
#define pinBase 100
#define Taux_echantillonnage 0
#define Gain 0

// système de containers, permet d'activer et desactiver les modules
#define gyrosActive false
#define convActive false // ! compile, mais entre en boucle infinie sans capteur
#define tempActive false
#define gpsActive false
#define rtcActive false
#define magnetoActive false
#define gsmActive false
#define screenActive false
#define stepActive false

#define DELAYCLOCK 1000
#define DELAYGYROS 500
#define DELAYTEMP 1000

int main(void)
{
    // time manager
    std::chrono::time_point<std::chrono::system_clock> actualTime, previousTime, previousGyrosTime, previousTempTime; // ajouter une variable par bloc de délai
    previousTime = std::chrono::system_clock::now();
    previousGyrosTime = std::chrono::system_clock::now(); // donner une première valeur au bloc de délai
    previousTempTime = std::chrono::system_clock::now();
    long int diffTime, diffGyrosTime, diffTempTime; // ajouter une variable de comparaison

    // variables
    float gx = 0, gy = 0, gz = 0;
    float *p_gx = &gx, *p_gy = &gy, *p_gz = &gz;

    float tension = 0, courant = 0, puissance = 0;
    float *p_tension = &tension, *p_courant = &courant, *p_puissance = &puissance;

    float temp = 0;
    float *p_temp = &temp;

    char numero[20] = "\"+32494801130\"";
	char message[200] = "la température est très élevée (>25c).";

    wiringPiSetup();

    if (rtcActive)
    {
    }

    // Init Gyro
    if (gyrosActive)
    {
        MPU6050_Init();
    }

    if (gpsActive)
    {
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
    }

    // INIT

    while (1)
    {
        actualTime = std::chrono::system_clock::now(); // reprend le temps actuel

        diffTime = std::chrono::duration_cast<std::chrono::milliseconds>(actualTime - previousTime).count(); // calcule la différence depuis le dernier passage
        if (diffTime >= DELAYCLOCK)                                                                                // si diff de + de 1 sec
        {
            std::chrono::system_clock::time_point today = std::chrono::system_clock::now(); // ces trois
            std::time_t tt = std::chrono::system_clock::to_time_t(today);                   // lignes affichent
            std::cout << ctime(&tt);                                           // le temps actuel

            previousTime = std::chrono::system_clock::now(); // place la barre du dernier passage
        }

        if (rtcActive)
        {
        }

        if (gyrosActive)
        {
            diffGyrosTime = std::chrono::duration_cast<std::chrono::milliseconds>(actualTime - previousGyrosTime).count(); // délai de 500ms
            if (diffGyrosTime >= DELAYGYROS)
            {
                traitementGyro(p_gx, p_gy, p_gz);
                std::cout << "x= " << gx << ", y= " << gy << ", z= " << gz << std::endl;
                previousGyrosTime = std::chrono::system_clock::now();
            }
        }

        if (gpsActive)
        {
        }

        if (magnetoActive)
        {
        }

        if (convActive)
        {
            Convertisseur(p_tension, p_courant, p_puissance);

            std::cout << "tension = " << tension << " V" << std::endl;
            std::cout << "courant = " << courant << " A" << std::endl;
            std::cout << "puissance = " << puissance << " W" << std::endl;
        }

        if (stepActive)
        {
        }

        if (tempActive)
        {
            diffTempTime = std::chrono::duration_cast<std::chrono::milliseconds>(actualTime - previousTempTime).count(); // délai de 500ms
            if (diffTempTime >= DELAYTEMP)
            {
                try
                {
                    Temperature(p_temp);
                    std::cout << "temperature = " << temp << "°c" << std::endl;
                }
                catch (...)
                {
                    std::cout << "la temperature est mauvaise" << std::endl;
                }
                previousTempTime = std::chrono::system_clock::now();
            }
        }

        if (gsmActive)
        {
            if(temp >= 25.0f){
                SendSMS(numero, message);
            }
        }

        if (screenActive)
        {

            // les commandes suivantes devront être déplacées dans les boucle correspondantes une fois tout les modules implémentés
            // code de démonstration, veuillez remplacer les chiffres par les variables
            screenSetTemp(temp);

            screenSetPwr(puissance);

            screenSetPosition(50.460860f, 3.957098f);

            screenSetSignal(2);
        }
    }

    return 0;
}
