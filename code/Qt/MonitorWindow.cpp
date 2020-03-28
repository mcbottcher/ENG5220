#include "MonitorWindow.h"


#include <cmath> 

using namespace std;

MonitorWindow::MonitorWindow(size_t bufferSize, int16_t* dataPtr): 
    bufferSize(bufferSize),
    xAxisData(new double[bufferSize]()){
        
    // set up the initial plot data
	for(size_t i=0; i<bufferSize; i++ ){
		xAxisData[i] = i;
	}

    sensorDataPtr = dataPtr;


    accelerometerPlot = new QwtPlot;
    gyroPlot = new QwtPlot;
    fingerPlot = new QwtPlot;
    //Set plot titles
    accelerometerPlot->setTitle("Accelerometer");
    gyroPlot->setTitle("Gyroscope");
    fingerPlot->setTitle("Fingers");

    //construct all the curves
    acc = new Curve[3]{
        Curve(bufferSize,accelerometerPlot,"AccX",xAxisData),
        Curve(bufferSize,accelerometerPlot,"AccY",xAxisData),
        Curve(bufferSize,accelerometerPlot,"AccZ",xAxisData)
    };
    gyro = new Curve[3]{
        Curve(bufferSize,gyroPlot,"GyroX",xAxisData),
        Curve(bufferSize,gyroPlot,"GyroY",xAxisData),
        Curve(bufferSize,gyroPlot,"GyroZ",xAxisData)
    };
    finger = new Curve[5]{
        Curve(bufferSize,fingerPlot,"Index",xAxisData),
        Curve(bufferSize,fingerPlot,"Middle",xAxisData),
        Curve(bufferSize,fingerPlot,"Ring",xAxisData),
        Curve(bufferSize,fingerPlot,"Pinky",xAxisData),
        Curve(bufferSize,fingerPlot,"Thumb",xAxisData)
    };




    resetButton = new QPushButton("reset");
    closeButton = new QPushButton("close");

    connect(resetButton, &QPushButton::clicked, [this](){this->resetbutton();});
    connect(closeButton, &QPushButton::clicked, [this](){this->hide(); emit emitClose();});

 
    //setup and attach curves to plots (also colour them!)
    for (uint8_t i = 0; i < 5; i++){
        if (i < 3){
            acc[i].setupCurve();
            acc[i].curve->setPen(QColor(Qt::GlobalColor(Qt::red+i)));
            gyro[i].setupCurve();
            gyro[i].curve->setPen(QColor(Qt::GlobalColor(Qt::red+i)));
        }
        finger[i].setupCurve();
        finger[i].curve->setPen(QColor(Qt::GlobalColor(Qt::red+i)));
    }


    //plot initial curves
	drawPlots();

    //show plots
	accelerometerPlot->show();
	gyroPlot->show();
	fingerPlot->show();


	// set up the layout
	controlLayout = new QHBoxLayout;
    controlLayout->addStretch(400);
    controlLayout->addWidget(resetButton);
    controlLayout->addWidget(closeButton, Qt::AlignRight);

    accLayout = new QHBoxLayout;
    checkAccLayout = new QVBoxLayout;
    for (uint8_t i=0; i<3; i++){checkAccLayout->addWidget(acc[i].checkbox);}
    accLayout->addLayout(checkAccLayout);
    accLayout->addWidget(accelerometerPlot);
    
    gyroLayout  = new QHBoxLayout;
    checkGyroLayout = new QVBoxLayout;
    for (uint8_t i=0; i<3; i++){checkGyroLayout->addWidget(gyro[i].checkbox);}
    gyroLayout->addLayout(checkGyroLayout);
    gyroLayout->addWidget(gyroPlot);

    fingerLayout = new QHBoxLayout;
    checkFingerLayout = new QVBoxLayout;
    for (uint8_t i=0; i<5; i++){checkFingerLayout->addWidget(finger[i].checkbox);}
    fingerLayout->addLayout(checkFingerLayout);
    fingerLayout->addWidget(fingerPlot);

    //main layout
    hPlotLayout = new QHBoxLayout;
    hPlotLayout->addLayout(accLayout);
    hPlotLayout->addLayout(gyroLayout);

    vPlotLayout = new QVBoxLayout;
    vPlotLayout->addLayout(fingerLayout);
    vPlotLayout->addLayout(hPlotLayout);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(vPlotLayout);
    mainLayout->addLayout(controlLayout);
    setMinimumSize(300,300);
    setLayout(mainLayout);
}

MonitorWindow::~MonitorWindow(){
    delete[] xAxisData;
}


// Method to draw all plots on the screen
void MonitorWindow::drawPlots(){
    accelerometerPlot->replot();
    gyroPlot->replot();
    fingerPlot->replot();
}



void MonitorWindow::resetbutton(){
    for (uint8_t i=0;i<5;i++){
        if (i < 3){
            acc[i].resetCurve();
            gyro[i].resetCurve();
        }
        finger[i].resetCurve();
    }
}

void MonitorWindow::handleSamples(){
    for(int i=0; i<3; i++){
        acc[i].plotSample(sensorDataPtr[i]);
        gyro[i].plotSample(sensorDataPtr[i+3]);
    } 
    for(int i=0; i<5; i++){
        finger[i].plotSample(sensorDataPtr[i+6]);
    }
}