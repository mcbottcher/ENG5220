#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MonitorWindow.h"
#include "InterpretWindow.h"
#include "TrainWindow.h"
#include "../FilterBank.h"
#include "SampleTimer.h"
#include "config.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QToolButton>
#include <QFont>
#include <QThread>
#include <QtConcurrent>
#include <QThread>

#include <iostream>
#include <cmath> 

#define DATA_SAMPLE_INTERVAL 1000000000/SAMPLE_RATE //in nanoseconds

#define NUMBER_OF_FILTERS 10 //number of filters in each filter bank
#define ORDER_OF_FILTERS 4  //order of these filters


#define MONITOR_REFRESH_RATE 300 //in msec
#define NUMBER_OF_PLOT_SAMPLES 50
#define PLOT_BUFFER_SIZE 1

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        // size_t NUMBER_OF_PLOT_SAMPLES = 10;
        MonitorWindow *monitorWindow;
        InterpretWindow *interpretWindow;
        TrainWindow *trainWindow;
        QPixmap *logo_image;
        QFont title_font;
        QLabel *title_text, *logo, *lab_train, *lab_interpret, *lab_mon, *lab_icon;
        QPushButton *but_train, *but_interpret, *but_mon, *but_quit;
        QTimer *windowtimer, *moitorRefreshtimer;
        //QToolButton *logo_icon;
        //QVBoxLayout main_layout;
        // double filterCuttoffFreqs[10] = {0.01,1,1,1,2,2,3,3,4,4}; //cutoff frequencies for filters
        // FilterBank *accelFilterBank; //depreciated?
        // FilterBank *gyroFilterBank;
        // FilterBank *fingerFilterBank;
        SampleTimer  *cppSampleTimer;

        void createUI();
        void createFilters();
        int count = 0;

        // void timerEvent();

        double samplefinger[5][1];
        double sampleacc[3][1];
        double samplegyro[3][1];
	
    private slots:
        void timerEvent(); //depreciated: used to plot sinewave to curves 
        void newDataEvent();
        void monitor_button_clicked();
        void interpretButtonClicked();
        void interpretHome();
        void trainButtonClicked();
        void but_quit_clicked();
                

};

#endif // MAINWINDOW_H
