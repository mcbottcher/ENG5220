//TODO check if all of these are needed???
#include <unistd.h>
#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>

#include "cppTimer/CppTimer.h"
#include "MPU6050/MPU6050.h"
#include "MPU6050/I2Cdev.h"
#include "MCP3428/MCP3428.h"

#define MPU6050_I2C_ADDRESS 0x69
#define MCP3428_I2C_ADDRESS 0x6e
#define MPU3421_I2C_ADDRESS 0x68

#define NUMBER_OF_FINGERS 4

//accelerometer and gyroscope values
static int16_t ax, ay, az;
static int16_t gx, gy, gz;
//finger values
static int16_t finger_value[NUMBER_OF_FINGERS];
static int16_t thumb_value;

//TODO check if the splitting of file descriptors is an issue...
MPU6050 motionSensor(MPU6050_I2C_ADDRESS);
MCP3428 flexFingers(MCP3428_I2C_ADDRESS);
MCP3428 flexThumb(MCP3421_I2C_ADDRESS);

void sampleSensors(){

	motionSensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	for(int i=0; i<NUMBER_OF_FINGERS; i++){
		finger_value[i] = flexFingers.readChannel(i);
	}
	thumb_value = flexThumb.readChannel(i);
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

	//TODO put the config in a structure...
	flexFingers.setConfig(	CONFIG_INIT_CONVERSION,
				CONFIG_CH1,
				CONFIG_CONTINOUS_CONVERSION_MODE,
				CONFIG_12BIT_240SPS,
				CONFIG_GAIN_1X	);

	flexThumb.setConfig(	CONFIG_INIT_CONVERSION,
				CONFIG_CH1,
				CONFIG_CONTINOUS_CONVERSION_MODE,
				CONFIG_12BIT_240SPS,
				CONFIG_GAIN_1X	);


	Ticker sampleTimer;
	sampleTimer.start(100000000); //time in ns == 100ms
	printf("Timer Setup!\n\r");

	

}
