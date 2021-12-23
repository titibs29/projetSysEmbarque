#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "libs/screen.h"



int mainScreen(void) {

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

int mainGyros() {

	float Gyro_x, Gyro_y, Gyro_z;
	float Gx = 0, Gy = 0, Gz = 0;
	fd = wiringPiI2CSetup(Device_Address);   /*Initializes I2C with device Address*/
	MPU6050_Init();		                 /* Initializes MPU6050 */

	while (1)
	{

		Gyro_x = read_raw_data(GYRO_XOUT_H);
		Gyro_y = read_raw_data(GYRO_YOUT_H);
		Gyro_z = read_raw_data(GYRO_ZOUT_H);

		Gx = Gyro_x / 131;
		Gy = Gyro_y / 131;
		Gz = Gyro_z / 131;

		printf("\n Gx=%.3f °/s\tGy=%.3f °/s\tGz=%.3f °/s\t", Gx, Gy, Gz);
		delay(500);

	}
	return 0;
}