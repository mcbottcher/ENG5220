#include "MonitorWindow.h"
// #include "adcreader.h"

#include <cmath>  // for sine stuff

MonitorWindow::MonitorWindow(): count(0){
	

    resetButton = new QPushButton("reset");
    closeButton = new QPushButton("close");

    connect(resetButton, SIGNAL(clicked()), SLOT(resetbutton()));
    connect(closeButton, SIGNAL(clicked()), SLOT(closeWindow()));


	// set up the initial plot data
	for( int index=0; index<plotDataSize; ++index ){
		xAxisData[index] = index;
        for(int j = 0; j<3;j++){
            acc[j].data[index] = 0;
            gyro[j].data[index] = 0;
        }
        for (int j = 0; j<5;j++){finger[j].data[index]=0;}
	}

    //setup curve names
    acc[0].name = "AccX";
    acc[1].name = "AccY";
    acc[2].name = "AccZ";

    gyro[0].name = "GyroX";
    gyro[1].name = "GyroY";
    gyro[2].name = "GyroZ";

    finger[0].name = "Thumb";
    finger[1].name = "Index";
    finger[2].name = "Middle";
    finger[3].name = "Ring";
    finger[4].name = "Pinky";


    //setup checkboxes
    for (int i = 0; i < 3; i++){
        acc[i].checkbox = new QCheckBox(acc[i].name);
        gyro[i].checkbox = new QCheckBox(gyro[i].name);
    }

    for (int i = 0; i < 5; i++){finger[i].checkbox = new QCheckBox(finger[i].name);}


    //setup Plots
    accelerometerPlot = new QwtPlot;
    gyroPlot = new QwtPlot;
    fingerPlot = new QwtPlot;

    //attach curves to plots and set pen colour
    for (int i = 0; i < 3; i++){
        acc[i].plot = accelerometerPlot;
        setupCurves(acc[i]);
        acc[i].curve->setPen(QColor(Qt::GlobalColor(Qt::red+i)));

        gyro[i].plot = gyroPlot;
        setupCurves(gyro[i]);
        gyro[i].curve->setPen(QColor(Qt::GlobalColor(Qt::red+i)));
    }
    for (int i = 0; i < 5; i++){
        finger[i].plot = fingerPlot;
        setupCurves(finger[i]);
        finger[i].curve->setPen(QColor(Qt::GlobalColor(Qt::red+i)));
    }


    //show plots
	accelerometerPlot->replot();
	accelerometerPlot->show();
    gyroPlot->replot();
	gyroPlot->show();
    fingerPlot->replot();
	fingerPlot->show();


	// set up the layout
	controlLayout = new QVBoxLayout;
    controlLayout->addWidget(resetButton);
    controlLayout->addWidget(closeButton);

    accLayout = new QHBoxLayout;
    checkAccLayout = new QVBoxLayout;
    for (int i=0; i<3; i++){checkAccLayout->addWidget(acc[i].checkbox);}
    accLayout->addLayout(checkAccLayout);
    accLayout->addWidget(accelerometerPlot);
    
    gyroLayout  = new QHBoxLayout;
    checkGyroLayout = new QVBoxLayout;
    for (int i=0; i<3; i++){checkGyroLayout->addWidget(gyro[i].checkbox);}
    gyroLayout->addLayout(checkGyroLayout);
    gyroLayout->addWidget(gyroPlot);

    fingerLayout = new QHBoxLayout;
    checkFingerLayout = new QVBoxLayout;
    for (int i=0; i<5; i++){checkFingerLayout->addWidget(finger[i].checkbox);}
    fingerLayout->addLayout(checkFingerLayout);
    fingerLayout->addWidget(fingerPlot);

    //main layout
    hPlotLayout = new QHBoxLayout;
    hPlotLayout->addLayout(accLayout);
    hPlotLayout->addLayout(gyroLayout);

    vPlotLayout = new QVBoxLayout;
    vPlotLayout->addLayout(fingerLayout);
    vPlotLayout->addLayout(hPlotLayout);

	hLayout = new QHBoxLayout;
	hLayout->addLayout(controlLayout);
    hLayout->addLayout(vPlotLayout);

	setLayout(hLayout);
}

MonitorWindow::~MonitorWindow(){
}


// Method to draw a curve on a plot
void MonitorWindow::plotHandler(CurveStruct &plotcurve){
    plotcurve.curve->setSamples(xAxisData, plotcurve.data, plotDataSize);
    plotcurve.plot->replot();
}

void MonitorWindow::insertSample(CurveStruct &plotcurve, double sample){
    memmove(plotcurve.data, plotcurve.data+1, (plotDataSize-1) * sizeof(double));
	plotcurve.data[plotDataSize-1] = sample;
}

// Method to setup curves and attach to plot
void MonitorWindow::setupCurves(CurveStruct &plotcurve){
    plotcurve.curve = new QwtPlotCurve();
    plotcurve.curve->setSamples(xAxisData, plotcurve.data, plotDataSize);
	plotcurve.curve->attach(plotcurve.plot);
    resetCurve(plotcurve);
}

// Method to reset the Curves to Zero
void MonitorWindow::resetCurve(CurveStruct &plotcurve){
    for( int index=0; index<plotDataSize; ++index ){
		plotcurve.data[index] = 0;
	}
    plotcurve.curve->setSamples(xAxisData, plotcurve.data, plotDataSize);
    plotcurve.plot->replot();
}

// Method to plot sample if button is checked
void MonitorWindow::plotSample(CurveStruct &plotcurve, double sample){

    if (plotcurve.checkbox->isChecked()){
        insertSample(plotcurve, sample);
    }
    else {insertSample(plotcurve, 0);}

    plotHandler(plotcurve);
}

void MonitorWindow::timerEvent(QTimerEvent *){
	double sample = 5 * sin(M_PI * count/50.0);
	++count;

    plotSample(acc[0], sample);
    plotSample(acc[1], sample/2);
    plotSample(acc[2], sample/3);

    plotSample(gyro[0], sample);
    plotSample(gyro[1], sample/2);
    plotSample(gyro[2], sample/3);

    plotSample(finger[0], sample);
    plotSample(finger[1], sample/2);
    plotSample(finger[2], sample/3);
    plotSample(finger[3], sample/4);
    plotSample(finger[4], sample/5);

}


void MonitorWindow::resetbutton(){
    for (int i=0;i<3;i++){
        resetCurve(acc[i]);
        resetCurve(gyro[i]);
    }
    for (int i=0;i<5;i++){resetCurve(finger[i]);}
}
