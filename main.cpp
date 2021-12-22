#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "screen.h"
#include "libs/Convertisseur_puissance.h"
#include "libs/Temperature.h"



int main(void) {

    //Init Convertisseur_température
    mcp3422Setup(pinBase, ADDR_I2C, Taux_echantillonnage, Gain);

    //Init Capteur_Température
    max31855Setup(200, 0);


    wiringPiSetup();


    //INIT
    Init();
 
    // changement de temp�rature
    double temp = 16.0;
    setTemp(temp);

    //changement de puissance
    double pwr = 3650.0;
    setPwr(pwr);

    //changement de coordon�es g�ographique
    setPosition(50.411986, 4.442602);
    

    //changement de puissance du signal
    int signal = 2;
    setSignal(signal);


    int hmi = status();
    std::cout << "status: " << hmi << std::endl;
    close();


    while(1)
    
    {
    
    
    
    }
	return 0;

}