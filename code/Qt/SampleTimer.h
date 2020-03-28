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
#include <QMutex>


#include "../MCP3428/MCP3428.h"
#include "../MPU6050/MPU6050.h"


//! Sample Timer Class
/*!
    Class to plot perform data aquisition from the sensors.
    \sa CppTimer()
    \sa QObject()
*/
class SampleTimer : public QObject, public CppTimer
{
    Q_OBJECT
    private:
        //! mtx mutex.
        /*! A mutex to lock the data while the sampling is occuring. */
        QMutex *mtx;
        //! Motion sensor pointer.
        /*! A pointer to the MPU6050 for data acquision from the Accelerometer/Gyroscope. */
        MPU6050  *motionSensor;
        //! Finger sensors pointer.
        /*! A pointer to the MCP3428 for data acquision from the four fingers. */
        MCP3428  *flexFingers;
        //! Thumb sensor pointer.
        /*! A pointer to the MCP3428 for data acquision from the thumb sensor. */
        MCP3428  *flexThumb;

        //! sensorValues pointer.
        /*! Where the data from the sensors is stored. */     
        int16_t sensorValues[NUMBER_OF_SENSORS];

        //! readFromSensors method.
        /*! A method to capture the data from the various sensors and place them in the sensorValues array. 
            \note This method emits a QT signal upon completion of data acquision to let the main window know that there is data ready.
            \sa sensorValues and timeoutsignal()
        */
        inline void readFromSensors();
        


        
    public:
        //! Class constructor.
        /*! Default constructor to setup the sensors with the required configurations. */
        SampleTimer();
	    ~SampleTimer();

        //! timerEvent method.
        /*! Overridden method of CppTimer to call once timer has timed out. */
        void timerEvent();

        //! getSensorValues function.
        /*! Return a pointer to the captured sensor values so we can process the captured samples.*/
        int16_t* getSensorValues(){return sensorValues;}

    signals:
        //! timeoutsignal signal.
        /*! Qt signal to emit once data has been succsesfully captured.*/
        void timeoutsignal();
            
};

#endif // SAMPLETIMER_H
