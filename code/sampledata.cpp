//TODO check if all of these are needed???
#include <unistd.h>
#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>

#include "cppTimer/CppTimer.h"
#include "MPU6050/MPU6050.h"
//#include "MPU6050/I2Cdev.h"
#include "MCP3428/MCP3428.h"
#include "RingBuff.h"

#define SAMPLE_RATE_Hz 10
#define SAMPLE_TIME_SECONDS 2

#define NUMBER_OF_BUFFER_ELEMENTS SAMPLE_RATE_Hz*SAMPLE_TIME_SECONDS

#define ONE_NANO_SECOND 1000000000

#define MPU6050_I2C_ADDRESS 0x69
#define MCP3428_I2C_ADDRESS 0x6e
#define MCP3421_I2C_ADDRESS 0x68

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

//TODO make another class that can create an array of RingBuffs
RingBuff buff_accel_x(NUMBER_OF_BUFFER_ELEMENTS);
RingBuff buff_accel_y(NUMBER_OF_BUFFER_ELEMENTS);
RingBuff buff_accel_z(NUMBER_OF_BUFFER_ELEMENTS);
RingBuff buff_gyro_x(NUMBER_OF_BUFFER_ELEMENTS);
RingBuff buff_gyro_y(NUMBER_OF_BUFFER_ELEMENTS);
RingBuff buff_gyro_z(NUMBER_OF_BUFFER_ELEMENTS);
RingBuff buff_finger1(NUMBER_OF_BUFFER_ELEMENTS);
RingBuff buff_finger2(NUMBER_OF_BUFFER_ELEMENTS);
RingBuff buff_finger3(NUMBER_OF_BUFFER_ELEMENTS);
RingBuff buff_finger4(NUMBER_OF_BUFFER_ELEMENTS);
RingBuff buff_thumb(NUMBER_OF_BUFFER_ELEMENTS);

void sampleSensors(){

	motionSensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	for(int i=0; i<NUMBER_OF_FINGERS; i++){
		finger_value[i] = flexFingers.readChannel(i);
	}
	thumb_value = flexThumb.readChannel(1);
}

void insertDataToBuff(){
	
	buff_accel_x.insertSample(ax);
	buff_accel_y.insertSample(ay);
	buff_accel_z.insertSample(az);
	buff_gyro_x.insertSample(gx);
	buff_gyro_y.insertSample(gy);
	buff_gyro_z.insertSample(gz);
	buff_finger1.insertSample(finger_value[0]);
	buff_finger2.insertSample(finger_value[1]);
	buff_finger3.insertSample(finger_value[2]);
	buff_finger4.insertSample(finger_value[3]);
	buff_thumb.insertSample(thumb_value);

}

class Ticker : public CppTimer{

	void timerEvent(){
		sampleSensors();
		insertDataToBuff();
	}
};



/* **************************************************************************** */

int main(){

	motionSensor.initialize();	
	printf(motionSensor.testConnection() ? "MPU6050 connection successful\r\n" : "MPU6050 connection failed\r\n");

	//TODO put the config in a structure...
	flexFingers.setConfig(	CONFIG_INIT_CONVERSION,
				CONFIG_CHN1,
				CONFIG_CONTINUOUS_CONVERSION_MODE,
				CONFIG_12BIT_240SPS,
				CONFIG_GAIN_1X	);

	flexThumb.setConfig(	CONFIG_INIT_CONVERSION,
				CONFIG_CHN1,
				CONFIG_CONTINUOUS_CONVERSION_MODE,
				CONFIG_12BIT_240SPS,
				CONFIG_GAIN_1X	);


	Ticker sampleTimer;
	sampleTimer.start(ONE_NANO_SECOND/SAMPLE_RATE_Hz); 
	printf("Timer Setup!\n\r");

	while(1){

	}

}
