#ifndef MONITORWINDOW_H
#define MONITORWINDOW_H


#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include <QBoxLayout>
#include <QColor>
#include <QCheckBox>
#include <QPushButton>
#include <QString>


// class definition 'MonitorWindow'
class MonitorWindow : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

// internal variables for the window class

private:
    int count;
    const size_t bufferSize;
	
    QPushButton  *resetButton, *closeButton;

	QwtPlot      *accelerometerPlot, *gyroPlot, *fingerPlot;

    static const int plotDataSize = 200;
    double xAxisData[plotDataSize];

    struct CurveStruct{
        QwtPlot      *plot;
        QwtPlotCurve *curve;
        QCheckBox    *checkbox;
        double        data[plotDataSize];
        QString       name;
    } acc[3], gyro[3], finger[5];


	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QHBoxLayout  *controlLayout;  // vertical layout
    
    QVBoxLayout  *vPlotLayout;  
    QHBoxLayout  *hPlotLayout;
	QVBoxLayout  *mainLayout;  

    QVBoxLayout *checkAccLayout, *checkGyroLayout, *checkFingerLayout;
    QHBoxLayout *accLayout, *gyroLayout, *fingerLayout;

    void _updateCurve(CurveStruct &plotcurve);
    void _drawPlot(CurveStruct &plotcurve);
    void _insertSample(CurveStruct &plotcurve, double sample);
    void _setupCurves(QwtPlot *plot, CurveStruct &plotcurve);
    void _plotSample(CurveStruct &plotcurve, double sample);
    void _plotSample(CurveStruct &plotcurve, double *buffer);
    void _resetCurve(CurveStruct &plotcurve);


public:

	MonitorWindow(size_t bufferSize); // default constructor - called when a Window is declared without arguments
	~MonitorWindow();
	void timerEvent( QTimerEvent * );

    //plot individual samples in format: 
    //  sample[3] = {X,Y,Z}; or samples[3][n] = {{nX},{nY},{nZ}};
    template <typename T>
    void plotAcc(T sample);
    template <typename T>
    void plotGyro(T sample);
    template <typename T>
    void plotFinger(T sample);

    // draw all plots
    void drawPlots();


    

public slots:

    void resetbutton();
    void closeWindow(){this->hide();}

};

#endif // MONITORWINDOW_H