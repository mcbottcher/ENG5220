#include "sampledata.h"

Sample::Sample(){

    _motionSensor.initialize();	
    //printf(motionSensor.testConnection() ? "MPU6050 connection successful\r\n" : "MPU6050 connection failed\r\n");

	_flexFingers.setConfig(CONFIG_INIT_CONVERSION,
				          CONFIG_CHN1,
				          CONFIG_CONTINUOUS_CONVERSION_MODE,
				          CONFIG_12BIT_240SPS,
				          CONFIG_GAIN_1X);

	_flexThumb.setConfig(CONFIG_INIT_CONVERSION,
				        CONFIG_CHN1,
				        CONFIG_CONTINUOUS_CONVERSION_MODE,
				        CONFIG_12BIT_240SPS,
				        CONFIG_GAIN_1X);

}

Sample::~Sample(){

}

void Sample::run(){
        
    _readfromSensors();
    //TODO emit signal here :)
    
}

int16_t* Sample::getSensorValues(){
    return &_sensorValues;
}

void Sample::_readfromSensors(){

    //TODO put a lock on this data?   
    _motionSensor.getMotion6(&_sensorValues[0],
                             &_sensorValues[1],
                             &_sensorValues[2],
                             &_sensorValues[3],
                             &_sensorValues[4],
                             &_sensorValues[5]);
    
	_sensorValues[6] = _flexFingers.readChannel(0);
	_sensorValues[7] = _flexFingers.readChannel(1);
	_sensorValues[8] = _flexFingers.readChannel(2);
	_sensorValues[9] = _flexFingers.readChannel(3);
    _sensorValues[10] = _flexThumb.readChannel(0);
}



