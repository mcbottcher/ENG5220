#include <unistd.h>
#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>

#include "MCP3428/MCP3428.h"
#include "MPU6050/MPU6050.h"

#define NUMBER_OF_SENSORS 11

#define MPU6050_I2C_ADDRESS 0x69
#define MCP3428_I2C_ADDRESS 0x6e
#define MCP3421_I2C_ADDRESS 0x68

class Sample{

    public:
        Sample();
        ~Sample();
    
        void run();
    
        int16_t* getSensorValues();    
    
    private:
    
        MPU6050 _motionSensor(MPU6050_I2C_ADDRESS);
        MCP3428 _flexFingers(MCP3428_I2C_ADDRESS);
        MCP3428 _flexThumb(MCP3421_I2C_ADDRESS);
        
        void _readfromSensors();
        
        int16_t _sensorValues[NUMBER_OF_SENSORS];
    
};
