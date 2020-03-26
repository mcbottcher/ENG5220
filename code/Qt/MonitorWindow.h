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
class MonitorWindow : public QWidget {
// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
Q_OBJECT

private:
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
        \sa bufferSize and MonitorWindow() */
    double *xAxisData;

    //! sensorData pointer.
    /*! Pointer to where new samples will be stored when the arrive.
        \sa SampleTimer(), newDataEvent() and MainWindow() */
    int16_t* sensorDataPtr;


    //! CurveStruct data structure.
    /*! Data structure for each curve on the graphs. */
    typedef struct Curve{
        const size_t  buffsize; /*!< Length of the ploting buffer */
        QString       name;     /*!< The name of each curve so the user knows what curve is what data. */
        double       *data;     /*!< Pointer to the data held in memory for that curve. */
        QwtPlot      *plot;     /*!< The associated QwtPlot for the curve. */
        QwtPlotCurve *curve;    /*!< The actual curve object itsself. */
        QCheckBox    *checkbox; /*!< Checkbox to turn the curve on and off. */
        double       *xAxisData;/*!< Pointer to the xAxis data */


        //! Curve constructor.
        /*! Plot a single samples if the checkbox has been selected by the user.
            \param buffsize The size of buffer for the plot.
            \param plotin   The plot that the curve is attached to.
            \param name     The name of the curve.
            \param xAxis    The xAxis data.
        */
        Curve(size_t buffsize, QwtPlot *plotin, QString name, double *xAxis): 
                buffsize(buffsize), name(name), data(new double[buffsize]()){

            curve = new QwtPlotCurve();
            plot = plotin;
            xAxisData = xAxis;
            checkbox = new QCheckBox(name);
            for (size_t i =0; i<buffsize; i++){data[i] = 0;}

        }
        //! Default Curve destuctor.
        ~Curve(){
            delete[] data;
        }

        //! updateCurve method.
        /*! Method to set the samples of a curve with the data held in its CurveStruct.*/
        void updateCurve(){
            curve->setRawSamples(xAxisData, data, buffsize);
        }
        //! resetCurve method.
        /*! Method to rest the curve to zeros*/
        void resetCurve(){
            for(size_t i=0; i<buffsize; i++){
                data[i] = 0;
            }
            updateCurve();
        }
        //! Attach curve to plot.
        void attach(){curve->attach(plot);}

        //! setupCuves method.
        /*! Helper Method setup and attach curves to their respective plot widgets.*/
        void setupCurve(){
            updateCurve();
            attach();
        }

        //! insertSample method.
        /*! Method to insert a sample into a curve.
            \param sample The sample to be added to the curve.
        */
        inline void insertSample(double sample){
            memmove(data, data+1, (buffsize-1) * sizeof(double));
            data[buffsize-1] = sample;
        }

        //! plotSample method.
        /*! Plot a single samples if the checkbox has been selected by the user.
            \param sample   The sample to be plotted.
            \sa checkbox and _insertSample()  
        */
        inline void plotSample(double sample){
            if (checkbox->isChecked()){
                insertSample(sample);
            }
            else{
                insertSample(0);
            }
            updateCurve();
        }

        //! plotSample method.
        /*! Plot a buffer of samples if the checkbox has been selected by the user.
            \param buffer    Pointer to the buffer to be plotted.
            \param plotSize The size of the buffer to be plotted. 
            \sa  insertSample() and checkbox
        */
        inline void plotSample(double *buffer, size_t plotSize){
            if (checkbox->isChecked()){
                for (size_t i=0; i< plotSize;i++){
                    insertSample(buffer[i]);
                }
            }
            else{
                for (size_t i=0; i< plotSize;i++){
                    insertSample(0);
                }
            }
            updateCurve();
        }
    } Curve_t;
    
    //! Curve structure for sensor data.
    /*! Create Curve class for each type of data.
        \sa Curve    
    */
    Curve_t *acc, *gyro, *finger;

    //! Vertical layout members.
    /*! Vertical QT layout elements of the GUI */
    QVBoxLayout *mainLayout, *vPlotLayout, *checkAccLayout, *checkGyroLayout, *checkFingerLayout;
    //! Horizontal layout members
    /*! Horizontal QT layout elements of the GUI */
    QHBoxLayout *controlLayout, *hPlotLayout, *accLayout, *gyroLayout, *fingerLayout;

public:

    //! Class constructor.
    /*! Setup the Window.
        \param bufferSize The length of buffers required for plotting.
    */
    MonitorWindow(size_t bufferSize, int16_t* dataPtr);
    //! Class destructor.
    /*! default destructor.
    */
    ~MonitorWindow();


    //! plotAcc helper method.
    /*! Plot a buffer of samples of varing length to the accelerometer graph. 
        \param samples  buffer to be plotted.
        \note pass samples in format: samples[3][n] = {{X0,X1,Xn},{Y0,Y1,Yn},{Z0,Z1,Zn}};
    */
    template <size_t plotBufferSize>
    void plotAcc(double (&samples)[3][plotBufferSize]){
        for (size_t i = 0; i < 3; i++){
            acc[i].plotSample(samples[i], plotBufferSize);
        }
    }

    //! plotGyro helper method.
    /*! Plot a buffer of samples of varing length to the gyroscope graph. 
        \param samples  buffer to be plotted. 
        \note pass samples in format: samples[3][n] = {{X0,X1,Xn},{Y0,Y1,Yn},{Z0,Z1,Zn}};
    */
    template <size_t plotBufferSize>
    void plotGyro(double (&samples)[3][plotBufferSize]){ 
        for (size_t i = 0; i < 3; i++){
            gyro[i].plotSample(samples[i], plotBufferSize);
        }
    }


    //! plotFinger helper method.
    /*! Plot a buffer of samples of varing length to the finger graph. 
        \param samples  buffer to be plotted.
        \note pass samples in format: samples[5][n] = {{IndexFingerArray}, {...}, {...},{PinkyFingerArray}, {ThumbArray}};
    */
    template <size_t plotBufferSize>
    void plotFinger(double (&samples)[5][plotBufferSize]){
        for (size_t i = 0; i < 5; i++){
            finger[i].plotSample(samples[i], plotBufferSize);
        }
    }


public slots:

    //! drawPlots method.
    /*! Public slot to allow refreshing of the screen and update the cruves onto the screen. */
    void drawPlots();

    //! resetbutton method.
    /*! Public slot to reset all the buffers to zero. */
    void resetbutton();

    //! handle samples.
    /*! Public slot to update the curves with new data*/
    void handleSamples();

};

#endif // MONITORWINDOW_H
