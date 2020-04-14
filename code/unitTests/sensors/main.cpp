#include <iostream>
#include "../../MPU6050/MPU6050.h"
#include "../../MCP3428/MCP3428.h"

#define MPU6050_I2C_ADDRESS 0x69
#define MCP3428_I2C_ADDRESS 0x6e
#define MCP3421_I2C_ADDRESS 0x68


int main(){
    int failflag = 0;

    try{
        int16_t sensorValues[6] = {0};
        uint8_t sensorcount=0;

        MPU6050 motionSensor(MPU6050_I2C_ADDRESS);
        motionSensor.initialize();
        if (!motionSensor.testConnection()){throw std::string("Device connection failed");}

        motionSensor.getMotion6(&sensorValues[0],
                            &sensorValues[1],
                            &sensorValues[2],
                            &sensorValues[3],
                            &sensorValues[4],
                            &sensorValues[5]);
        for (int i=0; i<6; i++){
            if (sensorValues[i]){sensorcount++;}
        }
        if (sensorcount != 6){throw std::string("Sensor fault");}


    }
    catch (std::string e){
        std::cout << "An exception occurred with MPU6050: " << e << '\n' << std::endl;
        failflag = -1;
    }

    try{

        MCP3428 flexFingers(MCP3428_I2C_ADDRESS);
        MCP3428 flexThumb(MCP3421_I2C_ADDRESS);

        flexFingers.setConfig(CONFIG_INIT_CONVERSION,
                        CONFIG_CHN1,
                        CONFIG_CONTINUOUS_CONVERSION_MODE,
                        CONFIG_12BIT_240SPS,
                        CONFIG_GAIN_1X);

        flexThumb.setConfig(CONFIG_INIT_CONVERSION,
                        CONFIG_CHN1,
                        CONFIG_CONTINUOUS_CONVERSION_MODE,
                        CONFIG_12BIT_240SPS,
                        CONFIG_GAIN_1X);

        int16_t fingers[4] = {0};
        for (int i =0;i<4;i++){
            fingers[i] = flexFingers.readChannel(i);
        }

  
        if ((fingers[0]==fingers[1])&&(fingers[2]==fingers[3])) {throw std::string("fingers channel fault: ");}
        
 
        int16_t thumb =0;

        thumb = flexThumb.readChannel(0);
        if (thumb == 0 ){throw std::string("thumb channel fault");}


    }
    catch (std::string e){
        std::cout << "An exception occurred with MCP3428: " << e << '\n' << std::endl;
        failflag = -1;
    }

    return failflag;
}