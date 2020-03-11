
#include "CppTimer.h"
#include "../RingBuff.h"
#include <QObject>
#include <QThread>

#define MPU6050_I2C_ADDRESS 0x69
#define MCP3428_I2C_ADDRESS 0x6e
#define MCP3421_I2C_ADDRESS 0x68


class SamplingThread : public QObject, public CppTimer
{

    Q_OBJECT
public:

    SamplingThread(){
        // static int16_t ax, ay, az;
        // static int16_t gx, gy, gz;
        // static int16_t finger_value[5];
        // static int16_t thumb_value;

        // MPU6050 motionSensor(MPU6050_I2C_ADDRESS);
        // MCP3428 flexFingers(MCP3428_I2C_ADDRESS);
        // MCP3428 flexThumb(MCP3421_I2C_ADDRESS);
    }


    void timerEvent(){
        emit timeoutsignal();
    }

signals:
    void timeoutsignal();

};