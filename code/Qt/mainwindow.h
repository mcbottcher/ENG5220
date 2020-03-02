#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MonitorWindow.h"
#include "InterpretWindow.h"
#include "TrainWindow.h"
#include "../FilterBank.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QToolButton>
#include <QFont>


#define SAMPLE_RATE 500 //in Hertz

#define NUMBER_OF_FILTERS 10 //number of filters in each filter bank
#define ORDER_OF_FILTERS 4  //order of these filters

#define MONITOR_REFRESH_RATE 100 //in msec
#define NUMER_OF_PLOT_SAMPLES 200

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    

private:
    // size_t NUMER_OF_PLOT_SAMPLES = 10;
    MonitorWindow *monitorWindow;
    InterpretWindow *interpretWindow;
    TrainWindow *trainWindow;
    QPixmap *logo_image;
    QFont title_font;
    QLabel *title_text, *logo, *lab_train, *lab_interpret, *lab_mon, *lab_icon;
    QPushButton *but_train, *but_interpret, *but_mon, *but_quit;
    QTimer *windowtimer, *moitortimer;
    //QToolButton *logo_icon;
    //QVBoxLayout main_layout;
    double filterCuttoffFreqs[10] = {0.01,5,10,20,30,40,50,100,150,200}; //cutoff frequencies for filters
    FilterBank *accelFilterBank;
    FilterBank *gyroFilterBank;
    FilterBank *fingerFilterBank;

    void createUI();
    void createFilters();

private slots:
    void monitor_button_clicked();
    void interpretButtonClicked();
    void interpretHome();
    void trainButtonClicked();
    void but_quit_clicked();

};

#endif // MAINWINDOW_H
