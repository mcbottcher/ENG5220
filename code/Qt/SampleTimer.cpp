
#include "SampleTimer.h"

SampleTimer::SampleTimer(){

    motionSensor = new MPU6050(MPU6050_I2C_ADDRESS);
    flexFingers = new MCP3428(MCP3428_I2C_ADDRESS);
    flexThumb = new MCP3428(MCP3421_I2C_ADDRESS);

    motionSensor->initialize();	
    //printf(motionSensor.testConnection() ? "MPU6050 connection successful\r\n" : "MPU6050 connection failed\r\n");

    flexFingers->setConfig(CONFIG_INIT_CONVERSION,
                        CONFIG_CHN1,
                        CONFIG_CONTINUOUS_CONVERSION_MODE,
                        CONFIG_12BIT_240SPS,
                        CONFIG_GAIN_1X);

    flexThumb->setConfig(CONFIG_INIT_CONVERSION,
                        CONFIG_CHN1,
                        CONFIG_CONTINUOUS_CONVERSION_MODE,
                        CONFIG_12BIT_240SPS,
                        CONFIG_GAIN_1X);

}

SampleTimer::~SampleTimer(){
    delete motionSensor;
    delete flexFingers;
    delete flexThumb;
}

inline void SampleTimer::readFromSensors(){
   
    mtx.lock();
    motionSensor->getMotion6(&sensorValues[0],
                            &sensorValues[1],
                            &sensorValues[2],
                            &sensorValues[3],
                            &sensorValues[4],
                            &sensorValues[5]);
    

    sensorValues[6]  = flexFingers->readChannel(2);
    sensorValues[7]  = flexFingers->readChannel(3);
    sensorValues[8]  = flexFingers->readChannel(1);
    sensorValues[9]  = flexFingers->readChannel(0);
    sensorValues[10] = flexThumb  ->readChannel(0);
    
    mtx.unlock();  

    emit timeoutsignal();
}

void SampleTimer::timerEvent(){
	
	//readFromSensors();
	emit timeoutsignal();
        
}

