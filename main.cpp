#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "libs/screen.h"
#include "libs/SMS.h"
#include "libs/Convertisseur_puissance.h"
#include "libs/Temperature.h"
#include "libs/gyroscope.h"
#include "libs/rtc.h"

//Define du convertisseur
#define ADDR_I2C 0x68							//Adresse en hexa de la communication I2C
#define pinBase 100                     
#define Taux_echantillonnage 0
#define Gain 0

#define gyrosActive true




int main(void) {

    //Init Gyro
    float gx =0, gy=0, gz=0;
    float* Gx = &gx;
    float* Gy = &gy;
    float* Gz = &gz;

    if(gyrosActive){
    MPU6050_Init();
    }


    //Init Convertisseur_température
    mcp3422Setup(pinBase, ADDR_I2C, Taux_echantillonnage, Gain);

    //Init Capteur_Température
    max31855Setup(200, 0);


    wiringPiSetup();


    //INIT
    Init();
 
   


    while(1)
    {
    
    if(gyrosActive){
        traitementGyro(*Gx, *Gy, *Gz);
        printf("x= %.2f, y= %.2f, z= %.2f", gx, gy, gz);
    }

    }
	return 0;

}


