#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "libs/screen.h"
#include "libs/SMS.h"
#include "libs/Convertisseur_puissance.h"
#include "libs/Temperature.h"
#include "libs/gyroscope.h"
#include "libs/rtc.h"
#include "libs/hmc5883l.h"

//Define du convertisseur
#define ADDR_I2C 0x68							//Adresse en hexa de la communication I2C
#define pinBase 100                     
#define Taux_echantillonnage 0
#define Gain 0

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



int main(void) {

    // variables
    float gx =0, gy=0, gz=0;
    float* p_gx = &gx;
    float* p_gy = &gy;
    float* p_gz = &gz;

    //Init Gyro
    if(gyrosActive){
    MPU6050_Init();
    }

    if(gpsActive){

    }

    if(rtcActive){

    }

    if(magnetoActive){

    }

    if(gsmActive){

    }

    if(screenActive){
    screenInit();
    }

    //Init Capteur_Température
    if(tempActive){
    max31855Setup(200, 0);

    }

    //Init Convertisseur_température
    if(convActive){
    mcp3422Setup(pinBase, ADDR_I2C, Taux_echantillonnage, Gain);

    }

    if(stepActive){

    }




    wiringPiSetup();


    //INIT

 
   


    while(1)
    {
    
    if(gyrosActive){
        traitementGyro(p_gx, p_gy, p_gz);
        printf("x= %.2f, y= %.2f, z= %.2f", gx, gy, gz);
    }
    
    if(gpsActive){

    }

    if(rtcActive){

    }

    if(magnetoActive){

    }

    if(gsmActive){

    }

    if(tempActive){

    }

    if(convActive){

    }
    if(stepActive){

    }

    if(screenActive){

        // code de démonstration, veuillez remplacer les chiffres par les variables 
    screenSetTemp(24.5);

    screenSetPwr(245.0);

    screenSetPosition(50.460860,3.957098);

    screenSetSignal(2);

    }

    }
	return 0;

}


