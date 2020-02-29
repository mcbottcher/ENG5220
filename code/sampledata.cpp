#include <unistd.h>
#include <stdio.h>
#include <stdint.h> 

#include "cppTimer/CppTimer.h"
#include "MPU6050/MPU6050.h"
#include "MPU6050/I2Cdev.h"

#define MPU6050_I2C_ADDRESS 0x69

//accelerometer and gyroscope values
static int16_t ax, ay, az;
static int16_t gx, gy, gz;

MPU6050 motionSensor(MPU6050_I2C_ADDRESS);


void sampleSensors(){

	motionSensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

}


class Ticker : public CppTimer{

	void timerEvent{
		sampleSensors();
		insertDataToBuff();
	}
}



/* **************************************************************************** */

int main(){

	motionSensor.initialize();	
	printf(motionSensor.testConnection() ? "MPU6050 connection successful\r\n" : "MPU6050 connection failed\r\n");

	Ticker sampleTimer;
	sampleTimer.start(100000000); //time in ns == 100ms
	printf("Timer Setup!\n\r");

	

}
