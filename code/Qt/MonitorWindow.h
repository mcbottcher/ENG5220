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

#include <QtConcurrent>
#include <QThreadPool>

#include <thread>


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


    double *xAxisData;

    typedef struct CurveStruct{
        QwtPlot      *plot;
        QwtPlotCurve *curve;
        QCheckBox    *checkbox;
        double       *data;
        QString       name;
    } CurveStruct_t;
    
    //typedef std::tuple<CurveStrcut_t[3], CurveStruct_t[3], CurvesStruct_t[5]> Spatials;
    //enum {acc=0, gryo, finger};
    //Spatials s;
    CurveStruct_t acc[3], gyro[3], finger[5];


	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QHBoxLayout  *controlLayout;  // vertical layout
    
    QVBoxLayout  *vPlotLayout;  
    QHBoxLayout  *hPlotLayout;
	QVBoxLayout  *mainLayout;  

    QVBoxLayout *checkAccLayout, *checkGyroLayout, *checkFingerLayout;
    QHBoxLayout *accLayout, *gyroLayout, *fingerLayout;

    void _updateCurve(CurveStruct &plotcurve);
    void _drawPlot(CurveStruct &plotcurve);
    inline void _insertSample(CurveStruct &plotcurve, double sample);
    void _setupCurves(QwtPlot *plot, CurveStruct &plotcurve);
    // void _plotSample(CurveStruct &plotcurve, double sample);
    void _plotSample(CurveStruct &plotcurve, const double *buffer, size_t plotBufferSize);
    void _resetCurve(CurveStruct &plotcurve);


public:

	MonitorWindow(size_t bufferSize); // default constructor - called when a Window is declared without arguments
	~MonitorWindow();
	// void timerEvent(QTimerEvent *);

    //plot individual samples in format: 
    //  sample[3] = {X,Y,Z}; or samples[3][n] = {{X0,X1,Xn},{Y0,Y1,Yn},{Z0,Z1,Zn}};
    template <size_t plotBufferSize>
    void plotAcc(double (&sample)[3][plotBufferSize]){
        // QtConcurrent::run([=]() {
            for (size_t i = 0; i < 3; i++){
                _plotSample(acc[i], sample[i], plotBufferSize);
            }
        // });
    }

    template <size_t plotBufferSize>
    void plotGyro(double (&sample)[3][plotBufferSize]){ 
        // QtConcurrent::run([=]() {
            for (size_t i = 0; i < 3; i++){
                _plotSample(gyro[i], sample[i], plotBufferSize);
            }
        // });
    }



    template <size_t plotBufferSize>
    void plotFinger(double (&sample)[5][plotBufferSize]){
        // QtConcurrent::run([=]() {
            for (size_t i = 0; i < 5; i++){
                _plotSample(finger[i], sample[i], plotBufferSize);
            }
        // });
    }



    

        

    // // draw all plots
    // void drawPlots();


    

public slots:

    // draw all plots
    void drawPlots();

    void resetbutton();

};

#endif // MONITORWINDOW_H