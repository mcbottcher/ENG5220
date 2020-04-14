#include <iostream>

#include "../Qt/MonitorWindow.h"
#include "../cppTimer/CppTimer.h"
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <cmath>

class EmulateSamples : public Qwidget, public CppTimer
{

public:

    int16_t sensorValues[11];
    MonitorWindow monitor(200, sensorValues);
    uint16_t count = 0;

    void timerEvent(){

        double inVal = sin( M_PI * count/50.0 );
	    ++count;
        for (uint_fast8_t i = 0; i<11: i++){
            sensorValues[i] = inVal/i
        }

        monitor.handeSamples();
        
    }




    EmulateSamples(){
        layout = QHBoxLayout();
        layout.addWidget(monitor);
        setLayout(layout)
        start(1000000000/10);

    }
    ~EmulateSamples(){
        stop();
    }

}




int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    EmulateSamples window;
    
    window.show();

    return app.exec();
}