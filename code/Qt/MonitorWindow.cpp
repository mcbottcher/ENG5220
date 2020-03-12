#include "MonitorWindow.h"


#include <cmath> 

using namespace std;

MonitorWindow::MonitorWindow(size_t bufferSize): 
    count(0),
    bufferSize(bufferSize),
    xAxisData(new double[bufferSize]()){
	
    for (int i=0; i<3; i++){
        acc[i].data = new double[bufferSize];
        gyro[i].data = new double[bufferSize];
    }
    for (int i=0; i<5; i++){
        finger[i].data = new double[bufferSize];
    }

    resetButton = new QPushButton("reset");
    closeButton = new QPushButton("close");

    connect(resetButton, &QPushButton::clicked, [this](){this->resetbutton();});
    connect(closeButton, &QPushButton::clicked, [this](){this->hide();});


	// set up the initial plot data
	for(size_t index=0; index<bufferSize; index++ ){
		xAxisData[index] = index;
        for(size_t j = 0; j<5;j++){
            if (j < 3){
                acc[j].data[index] = 0;
                gyro[j].data[index] = 0;
            }
            finger[j].data[index]=0;
        }
	}

    //setup curve names
    acc[0].name = "AccX";
    acc[1].name = "AccY";
    acc[2].name = "AccZ";

    gyro[0].name = "GyroX";
    gyro[1].name = "GyroY";
    gyro[2].name = "GyroZ";

    finger[0].name = "Index";
    finger[1].name = "Middle";
    finger[2].name = "Ring";
    finger[3].name = "Pinky";
    finger[4].name = "Thumb";


    //setup checkboxes
    for (size_t i = 0; i < 5; i++){
        if (i < 3){
            acc[i].checkbox = new QCheckBox(acc[i].name);
            gyro[i].checkbox = new QCheckBox(gyro[i].name);
        }
        finger[i].checkbox = new QCheckBox(finger[i].name);
    }

    //setup Plots
    accelerometerPlot = new QwtPlot;
    gyroPlot = new QwtPlot;
    fingerPlot = new QwtPlot;


    //setup and attach curves to plots
    for (size_t i = 0; i < 5; i++){
        if (i < 3){
            _setupCurves(accelerometerPlot, acc[i]);
            _setupCurves(gyroPlot, gyro[i]);
        }
        _setupCurves(fingerPlot, finger[i]);
    }

    //set colour of curves
    for (size_t i = 0; i < 5; i++){
        if (i < 3){
            acc[i].curve->setPen(QColor(Qt::GlobalColor(Qt::red+i)));
            gyro[i].curve->setPen(QColor(Qt::GlobalColor(Qt::red+i)));
        }
        finger[i].curve->setPen(QColor(Qt::GlobalColor(Qt::red+i)));
    }

    //Set plot titles
    accelerometerPlot->setTitle("Accelerometer");
    gyroPlot->setTitle("Gyroscope");
    fingerPlot->setTitle("Fingers");

    //pot initial curves
	accelerometerPlot->replot();
    gyroPlot->replot();
    fingerPlot->replot();

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
    for (size_t i=0; i<3; i++){checkAccLayout->addWidget(acc[i].checkbox);}
    accLayout->addLayout(checkAccLayout);
    accLayout->addWidget(accelerometerPlot);
    
    gyroLayout  = new QHBoxLayout;
    checkGyroLayout = new QVBoxLayout;
    for (size_t i=0; i<3; i++){checkGyroLayout->addWidget(gyro[i].checkbox);}
    gyroLayout->addLayout(checkGyroLayout);
    gyroLayout->addWidget(gyroPlot);

    fingerLayout = new QHBoxLayout;
    checkFingerLayout = new QVBoxLayout;
    for (size_t i=0; i<5; i++){checkFingerLayout->addWidget(finger[i].checkbox);}
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
    
}


// Method to draw on a curve
void MonitorWindow::_updateCurve(CurveStruct &plotcurve){
    plotcurve.curve->setSamples(xAxisData, plotcurve.data, bufferSize);
}

// Method to draw plot on the screen
void MonitorWindow::_drawPlot(CurveStruct &plotcurve){
    plotcurve.plot->replot();
}

// Method to draw all plots on the screen
void MonitorWindow::drawPlots(){
    accelerometerPlot->replot();
    gyroPlot->replot();
    fingerPlot->replot();
}

// Method to insert sample into curve data array
inline void MonitorWindow::_insertSample(CurveStruct &plotcurve, double sample){
    memmove(plotcurve.data, plotcurve.data+1, (bufferSize-1) * sizeof(double));
	plotcurve.data[bufferSize-1] = sample;
}

// Method to setup curves and attach to plot
void MonitorWindow::_setupCurves(QwtPlot *plot, CurveStruct &plotcurve){
    plotcurve.plot = plot;
    plotcurve.curve = new QwtPlotCurve();
    plotcurve.curve->setSamples(xAxisData,plotcurve.data, bufferSize);
	plotcurve.curve->attach(plotcurve.plot);
    _resetCurve(plotcurve);
}

// Method to reset the Curves to zero.
void MonitorWindow::_resetCurve(CurveStruct &plotcurve){
    for(size_t index=0; index<bufferSize; ++index ){
		plotcurve.data[index] = 0;
	}
    plotcurve.curve->setSamples(xAxisData, plotcurve.data, bufferSize);
}

// Method to plot individual sample if button is checked
// void MonitorWindow::_plotSample(CurveStruct &plotcurve, double sample){
//     if (plotcurve.checkbox->isChecked()){_insertSample(plotcurve, sample);}
//     else {_insertSample(plotcurve, 0);}
//     _updateCurve(plotcurve);
// }

// Method to plot buffer of samples if button is checked
void MonitorWindow::_plotSample(CurveStruct &plotcurve, const double *buffer, size_t plotBufferSize){
    if (plotcurve.checkbox->isChecked()){
        for (size_t i=0; i< plotBufferSize;i++){
            _insertSample(plotcurve, buffer[i]);
        }
    }
    else {
        for (size_t i=0; i< plotBufferSize;i++){
            _insertSample(plotcurve, 0);
        }
    }
    _updateCurve(plotcurve);
}



void MonitorWindow::resetbutton(){
    for (size_t i=0;i<5;i++){
        if (i < 3){
            _resetCurve(acc[i]);
            _resetCurve(gyro[i]);
        }
        _resetCurve(finger[i]);
    }
}


// // currently just showing use cases, should actually 
// // be used to update the plots at regular intervals
// void MonitorWindow::timerEvent(QTimerEvent *){

//     // //plot buffer of samples to each plot
//     // double **buffer;
//     // const int bufferlen = 10;
//     // buffer = new double*[5];
    
//     // for (size_t i = 0; i<5; i++){
//     //     buffer[i] = new double[bufferlen];
//     // }

//     // //fill buffers with samples
//     // for (size_t j = 0; j<bufferlen; j++){
//     //     double in = 5 * sin(M_PI * count/50.0);
// 	//     ++count;
//     //     for (size_t i=0; i<5;i ++){
//     //         buffer[i][j]= in/(i+1);
//     //     }
//     // }
    
//     // plotAcc(buffer);
//     // plotGyro(buffer);   
//     // plotFinger(buffer);
//     // drawPlots();

//     // delete[] buffer;

    
    

//     //plot single sample to each plot
//     double meh[5];

//     // double in = 5 * sin(M_PI * count/50.0);
// 	// ++count;

//     // for (size_t i=0; i<5;i++){
//     //     sample[i]= in/(i+1);
//     // }
    
//     // plotGyro(meh);   
//     // plotFinger(meh);
//     // drawPlots();
    


//     // //plot buffer of samples to each plot from instance
//     // double buffer[5][bufferSize];

//     // for (size_t i=0; i<bufferSize;i++){
//     //     double sample = 5 * sin(M_PI * count/50.0);
//     //     for (size_t j=0; j<5;j++ ){buffer[j][i] = sample/(j+1);}
//     //     ++count;
//     // }

//     // for (size_t i=0; i<5;i++){
//     //     if (i<3){
//     //         _plotSample(acc[i], buffer[i], bufferSize);
//     //         _plotSample(gyro[i], buffer[i], bufferSize);
//     //     }
//     //     _plotSample(finger[i], buffer[i], bufferSize);
//     // }
//     // drawPlots();


//     // //plot single sample to each plot from instance
//     // double sample = 5 * sin(M_PI * count/50.0);
// 	// ++count;

//     // for (size_t i=0; i<5;i++){
//     //     if (i<3){
//     //         _plotSample(acc[i], sample/(i+1));
//     //         _plotSample(gyro[i] sample/(i+1));
//     //     }
//     //     _plotSample(finger[i], sample/(i+1));
//     // }
//     // drawPlots();
// }



