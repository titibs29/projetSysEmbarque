#define Device_Address 0x68	/*Device Address/Identifier for MPU6050*/

#define PWR_MGMT_1   0x6B
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define INT_ENABLE   0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H  0x43
#define GYRO_YOUT_H  0x45
#define GYRO_ZOUT_H  0x47

int fd;
float Gyro_x, Gyro_y, Gyro_z;
float Gx = 0, Gy = 0, Gz = 0;

void MPU6050_Init() {

	fd = wiringPiI2CSetup(Device_Address); 

	wiringPiI2CWriteReg8(fd, SMPLRT_DIV, 0x07);	/* Write to sample rate register */
	wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0x01);	/* Write to power management register */
	wiringPiI2CWriteReg8(fd, CONFIG, 0);		/* Write to Configuration register */
	wiringPiI2CWriteReg8(fd, GYRO_CONFIG, 24);	/* Write to Gyro Configuration register */
	wiringPiI2CWriteReg8(fd, INT_ENABLE, 0x01);	/*Write to interrupt enable register */

}
short read_raw_data(int addr) {
	short high_byte, low_byte, value;
	high_byte = wiringPiI2CReadReg8(fd, addr);
	low_byte = wiringPiI2CReadReg8(fd, addr + 1);
	value = (high_byte << 8) | low_byte;
	return value;
}

void ms_delay(int val) {
	int i, j;
	for (i = 0; i <= val; i++)
		for (j = 0; j < 1200; j++);
}

<<<<<<< HEAD
=======
void traitementGyro() {
	Gyro_x = read_raw_data(GYRO_XOUT_H);
	Gyro_y = read_raw_data(GYRO_YOUT_H);
	Gyro_z = read_raw_data(GYRO_ZOUT_H);

	Gx = Gyro_x / 131;
	Gy = Gyro_y / 131;
	Gz = Gyro_z / 131;

	printf("\n Gx=%.3f °/s\tGy=%.3f °/s\tGz=%.3f °/s\t", Gx, Gy, Gz);
	delay(500);
}

int mainGyroscope() {

	MPU6050_Init();

	while (1)
	{
		traitementGyro();
	}
	return 0;
}
>>>>>>> 37a040206401847b21498f180a30c11d824dc613
