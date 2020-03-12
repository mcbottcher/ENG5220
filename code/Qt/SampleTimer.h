#ifndef SAMPLETIMER_H
#define SAMPLETIMER_H


#define NUMBER_OF_SENSORS 11

#define MPU6050_I2C_ADDRESS 0x69
#define MCP3428_I2C_ADDRESS 0x6e
#define MCP3421_I2C_ADDRESS 0x68

#include "../cppTimer/CppTimer.h"
#include "../RingBuff.h"

#include <unistd.h>
#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <QObject>


#include "../MCP3428/MCP3428.h"
#include "../MPU6050/MPU6050.h"



class SampleTimer : public QObject, public CppTimer
{
    Q_OBJECT
    private:

        MPU6050  *motionSensor;
        MCP3428  *flexFingers;
        MCP3428  *flexThumb;
        inline void readfromSensors();
        
        int16_t sensorValues[NUMBER_OF_SENSORS];


        
    public:
        // int16_t sensorValues[NUMBER_OF_SENSORS];
        SampleTimer();

        void timerEvent(){
            readfromSensors();
        }

        int16_t* getSensorValues(){return sensorValues;}

    signals:
        void timeoutsignal();
            
};

#endif // SAMPLETIMER_H