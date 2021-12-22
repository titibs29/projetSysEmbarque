#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "screen.h"







int main(void) {


    //INIT
    Init();

    // changement de température
    double temp = 16.0;
    setTemp(temp);

    //changement de puissance
    double pwr = 3650.0;
    setPwr(pwr);

    //changement de coordonées géographique
    setPosition(50.411986, 4.442602);
    

    //changement de puissance du signal
    int signal = 2;
    setSignal(signal);


    int hmi = status();
    std::cout << "status: " << hmi << std::endl;
    close();
    while(1){}
	return 0;

}