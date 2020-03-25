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



//!  Monitor Window Class
/*!
    Class to plot and monitor all the sensor data in real time
*/
class MonitorWindow : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT



    private:
        int count;
        //! bufferSize size_t.
        /*! The length of buffer for each plotting curve. Set by calling the constructor.
            \sa MonitorWindow()
        */
        const size_t bufferSize;
        
        //! Clickable button pointers.
        /*! Pointers to QPushButtons to allow user to close windows and reset buffers. */
        QPushButton  *resetButton, *closeButton;

        //! QwtPlot pointers.
        /*! Pointers to plots to allow curves to be added to. */
        QwtPlot      *accelerometerPlot, *gyroPlot, *fingerPlot;

        //! xAsisData pointer to a double.
        /*! xAxis data for plotting the curves will be filled by constructor with values 0 to bufferSize.
            \sa bufferSize
            \sa MonitorWindow() 
        */
        double *xAxisData;


        //! CurveStruct data structure.
        /*! Data structure for each curve on the graphs. */
        typedef struct CurveStruct{
            QwtPlot      *plot;     /*!< The associated QwtPlot for the curve. */
            QwtPlotCurve *curve;    /*!< The actual curve object itsself. */
            QCheckBox    *checkbox; /*!< Checkbox to turn the curve on and off. */
            double       *data;     /*!< Pointer to the data held in memory for that curve. */
            QString       name;     /*!< The name of each curve so the user knows what curve is what data. */
            ~CurveStruct(){
                delete[] data;
            }
        } CurveStruct_t;
        
        //! Data structure for sensor data.
        /*! Create data scructures for each type of data.
            \sa CurveStruct    
        */
        CurveStruct_t acc[3], gyro[3], finger[5];

        //! Vertical layout members.
        /*! Vertical QT layout elements of the GUI */
        QVBoxLayout *mainLayout, *vPlotLayout, *checkAccLayout, *checkGyroLayout, *checkFingerLayout;
        //! Horizontal layout members
        /*! Horizontal QT layout elements of the GUI */
        QHBoxLayout *controlLayout, *hPlotLayout, *accLayout, *gyroLayout, *fingerLayout;

        //! updateCurve method.
        /*! Method to set the samples of a specific curve with the data held in its CurveStruct
            \param plotcurve Pointer to the respective curve to be updated.
            \sa CurveStruct  
        */
        void _updateCurve(CurveStruct &plotcurve);

        //! drawPlot method.
        /*! Method to re-draw the curve on the screen.
            \param plotcurve Pointer to the respective curve to be replotted.
            \sa CurveStruct  
        */
        void _drawPlot(CurveStruct &plotcurve);

        //! insertSample method.
        /*! Method to insert a sample into a curve.
            \param plotcurve Pointer to the respective curve the sample should be added to.
            \param sample The sample to be added to the curve
            \sa CurveStruct  
        */
        inline void _insertSample(CurveStruct &plotcurve, double sample);

        //! setupCuves method.
        /*! Helper Method setup and attach curves to their respective plot widgets.
            \param plot The plot that the curve is to be attached to.
            \param plotcurve Pointer to the CurveStruct data structure.
            \sa CurveStruct  
        */
        void _setupCurves(QwtPlot *plot, CurveStruct &plotcurve);
        // void _plotSample(CurveStruct &plotcurve, double sample);

        //! plotSample method.
        /*! Plot a buffer of samples if the checkbox has been selected by the user.
            \param plotcurve Pointer to the CurveStruct data structure.
            \param buffer    Pointer to the buffer to be plotted.
            \param plotBufferSize The size of the buffer to be plotted. 
            \sa CurveStruct and _insertSample()  
        */
        void _plotSample(CurveStruct &plotcurve, const double *buffer, size_t plotBufferSize);

        //! resetCurve method.
        /*! Helper method to reset a curve to all zeros.*/
        void _resetCurve(CurveStruct &plotcurve);


    public:

        //! Class constructor.
        /*! Setup the Window.
            \param bufferSize The length of buffers required for plotting.
        */
        MonitorWindow(size_t bufferSize);
        //! Class destructor.
        /*! default destructor.
        */
        ~MonitorWindow();
        // void timerEvent(QTimerEvent *);

        //! plotAcc helper method.
        /*! Plot a buffer of samples of varing length to the accelerometer graph. 
            \param samples  buffer to be plotted.
            \note pass samples in format: samples[3][n] = {{X0,X1,Xn},{Y0,Y1,Yn},{Z0,Z1,Zn}};
        */
        template <size_t plotBufferSize>
        void plotAcc(double (&sample)[3][plotBufferSize]){
            for (size_t i = 0; i < 3; i++){
                _plotSample(acc[i], sample[i], plotBufferSize);
            }
        }

        //! plotGyro helper method.
        /*! Plot a buffer of samples of varing length to the gyroscope graph. 
            \param samples  buffer to be plotted. 
            \note pass samples in format: samples[3][n] = {{X0,X1,Xn},{Y0,Y1,Yn},{Z0,Z1,Zn}};
        */
        template <size_t plotBufferSize>
        void plotGyro(double (&sample)[3][plotBufferSize]){ 
            for (size_t i = 0; i < 3; i++){
                _plotSample(gyro[i], sample[i], plotBufferSize);
            }
        }


        //! plotFinger helper method.
        /*! Plot a buffer of samples of varing length to the finger graph. 
            \param samples  buffer to be plotted.
            \note pass samples in format: samples[5][n] = {{IndexFingerArray}, {...}, {...},{PinkyFingerArray}, {ThumbArray}};
        */
        template <size_t plotBufferSize>
        void plotFinger(double (&sample)[5][plotBufferSize]){
            for (size_t i = 0; i < 5; i++){
                _plotSample(finger[i], sample[i], plotBufferSize);
            }
        }

    public slots:

        //! drawPlots method.
        /*! Public slot to allow refreshing of the screen and update the cruves onto the screen. */
        void drawPlots();

        //! resetbutton method.
        /*! Public slot to reset all the buffers to zero. */
        void resetbutton();

};

#endif // MONITORWINDOW_H
