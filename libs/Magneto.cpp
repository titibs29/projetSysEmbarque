#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>       // atan2

#define DEVICE_ID 0x1E
#define REG_ConfA 0x00
#define REG_ConfB 0x01
#define REG_Register 0x02
#define REG_X_MSB 0x03
#define REG_X_LSB 0x04
#define REG_Z_MSB 0x05
#define REG_Z_LSB 0x06
#define REG_Y_MSB 0x07
#define REG_Y_LSB 0x08 



int main(int argc, char** argv)
{
    // Setup I2C communication
    int fd = wiringPiI2CSetup(DEVICE_ID);
    if (fd == -1) {
        std::cout << "Failed to init I2C communication.\n";
        return -1;
    }
    else std::cout << "I2C communication successfully setup.\n";

    wiringPiI2CWriteReg8(fd, REG_Register, 0x00); //continuous register mode
    wiringPiI2CWriteReg8(fd, REG_ConfB, 0x20); //gain = 1090

    while (1) {
        //variables brutes
        int X = (wiringPiI2CReadReg8(fd, REG_X_MSB) * 256 + wiringPiI2CReadReg8(fd, REG_X_LSB)) * 0.92;    //*0.92 car gain = 1090 
        int Y = (wiringPiI2CReadReg8(fd, REG_Y_MSB) * 256 + wiringPiI2CReadReg8(fd, REG_Y_LSB)) * 0.92;
        int Z = (wiringPiI2CReadReg8(fd, REG_Z_MSB) * 256 + wiringPiI2CReadReg8(fd, REG_Z_LSB)) * 0.92;
        /*
        if (X > 32767)
        {
            X -= 65536;
        }
        if (Y > 32767)
        {
            Y -= 65536;
        }
        if (Z > 32767)
        {
            Z -= 65536;
        }*/

        float direction = atan2(Y, X) ;
        if (direction < 0) direction += 2 * M_PI;
        if (direction > (2 * M_PI)) direction -= 2 * M_PI;
        direction = (direction * 180 / M_PI);



        std::cout << "X : " << X << "    Y : " << Y  << "    Z : " << Z << "\n"  << "angle : " << direction << "\n";
        delay(1000);


    }
    return 0;
}