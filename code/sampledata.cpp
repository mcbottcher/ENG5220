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

#define NUMBER_OF_REPETITIONS 20

#define SAMPLE_RATE_Hz 10
#define SAMPLE_TIME_SECONDS 2

#define NUMBER_OF_BUFFER_ELEMENTS SAMPLE_RATE_Hz*SAMPLE_TIME_SECONDS

#define ONE_NANO_SECOND 1000000000

#define MPU6050_I2C_ADDRESS 0x69
#define MCP3428_I2C_ADDRESS 0x6e
#define MCP3421_I2C_ADDRESS 0x68

#define NUMBER_OF_FINGERS 4


static int sample_counter = 0;

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

//11 == number of sensors, 
int16_t dataBuffer[11][NUMBER_OF_BUFFER_ELEMENTS];

void sampleSensors(){

	motionSensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	for(int i=0; i<NUMBER_OF_FINGERS; i++){
		finger_value[i] = flexFingers.readChannel(i);
	}
	thumb_value = flexThumb.readChannel(1);
}

void insertDataToBuff(){
	
	if(sample_counter < NUMBER_OF_BUFFER_ELEMENTS){
		dataBuffer[0][sample_counter] = ax;
		dataBuffer[1][sample_counter] = ay;
		dataBuffer[2][sample_counter] = az;
		dataBuffer[3][sample_counter] = gx;
		dataBuffer[4][sample_counter] = gy;
		dataBuffer[5][sample_counter] = gz;
		dataBuffer[6][sample_counter] = finger_value[0];
		dataBuffer[7][sample_counter] = finger_value[1];
		dataBuffer[8][sample_counter] = finger_value[2];
		dataBuffer[9][sample_counter] = finger_value[3];
		dataBuffer[10][sample_counter++] = thumb_value;
	}

}

class Ticker : public CppTimer{

	void timerEvent(){
		sampleSensors();
		insertDataToBuff();
	}
};


class Timer : public CppTimer{

	void timerEvent(){
		//set a flag here...	
	}
};


void countdown(){

	printf("Starting in 3\n\r");
	sleep(1);
	printf("2\n\r");
	sleep(1);
	printf("1\n\r");
	sleep(1);
	printf("GO!\n\n\r");

}

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
	
	
	

	for(int i=0; i<NUMBER_OF_REPETITIONS; i++){


		countdown();

		//start the ticker
		sampleTimer.start(ONE_NANO_SECOND/SAMPLE_RATE_Hz, PERIODIC);

		while(sample_counter < NUMBER_OF_BUFFER_ELEMENTS){
			
			sleep(1);
			

		}

		printf("STOP\n\r");

		//stop the ticker
		sampleTimer.disarm();

		//write to the file here!

		sleep(2);


	}

	printf("Finished!");
	
}
