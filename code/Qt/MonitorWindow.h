#ifndef WINDOW_H
#define WINDOW_H

#include <QString>

#include <qwt/qwt_knob.h>
#include <QPushButton>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include <QBoxLayout>
#include <QColor>
#include <QCheckBox>


// class definition 'MonitorWindow'
class MonitorWindow : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

// internal variables for the window class
private:
	
    QPushButton  *resetButton;
    QPushButton  *closeButton;


	QwtPlot      *accelerometerPlot;
    QwtPlot      *gyroPlot;
    QwtPlot      *fingerPlot;


    static const int plotDataSize = 100;
    double xAxisData[plotDataSize];

    struct CurveStruct{
        QwtPlot *plot;
        QwtPlotCurve *curve;
        QCheckBox *checkbox;
        double data[100];
        QString name;
    } acc[3], gyro[3], finger[5];


	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *controlLayout;  // vertical layout
    
    QVBoxLayout  *vPlotLayout;  // vertical layout
    QHBoxLayout  *hPlotLayout;
	QHBoxLayout  *hLayout;  // horizontal layout

    QVBoxLayout *checkAccLayout;
    QVBoxLayout *checkGyroLayout;
    QVBoxLayout *checkFingerLayout;

    QHBoxLayout *accLayout;
    QHBoxLayout *gyroLayout;
    QHBoxLayout *fingerLayout;

	int count;

public:

	MonitorWindow(); // default constructor - called when a Window is declared without arguments
	~MonitorWindow();
	void timerEvent( QTimerEvent * );

    void plotHandler(CurveStruct &plotcurve);
    void insertSample(CurveStruct &plotcurve, double sample);
    void setupCurves(CurveStruct &plotcurve);
    void plotSample(CurveStruct &plotcurve, double sample);
    void resetCurve(CurveStruct &plotcurve);
    

public slots:

    void resetbutton();
    void closeWindow(){this->close();}

};

#endif // WINDOW_H