#include "mainwindow.h"

#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent){
    
    createUI();
    //createFilters();

}


void MainWindow::createUI(){
    QPixmap pix("TheLexiconGlove.png");
    //QLabel icon_label;
    //icon_label.setPixmap(pix);
    //icon_label.setText("Test");
    pix = pix.scaledToWidth(300);
    
    lab_icon = new QLabel("Test", this);
    lab_icon->setPixmap(pix);

    //Add buttons and labels
    QFont title_font("Arial", 20, QFont::Bold);
    title_text = new QLabel("The Lexicon Glove", this);
    title_text->setFont(title_font);
    but_train = new QPushButton("Go", this);
    but_interpret = new QPushButton("Go", this);
    but_mon = new QPushButton("Go", this);
    but_quit = new QPushButton("Quit", this);
    lab_train = new QLabel("Training Mode", this);
    lab_interpret = new QLabel("Interpret Mode", this);
    lab_mon = new QLabel("Data Monitoring", this);

    //Horizontal layout  for title
    QHBoxLayout *title_layout = new QHBoxLayout;
    title_layout->addStretch(100);
    title_layout->addWidget(title_text);
    title_layout->addStretch(100);

    //Grid layout for buttons and labels
    QGridLayout *button_layout = new QGridLayout;
    button_layout->setHorizontalSpacing(10);
    button_layout->setVerticalSpacing(10);
    //button_layout->addWidget(logo);
    button_layout->addWidget(but_train, 0, 0, Qt::AlignCenter);
    button_layout->addWidget(lab_train, 0, 1);
    button_layout->addWidget(but_interpret, 1, 0, Qt::AlignCenter);
    button_layout->addWidget(lab_interpret, 1, 1);
    button_layout->addWidget(but_mon, 2, 0, Qt::AlignCenter);
    button_layout->addWidget(lab_mon, 2, 1);

    //Horizontal layout for Grid
    QHBoxLayout *grid_layout = new QHBoxLayout;
    grid_layout->addStretch(100);
    grid_layout->addLayout(button_layout);
    grid_layout->addStretch(100);

    //Horizontal layout for Quit button
    QHBoxLayout *quit_layout = new QHBoxLayout;
    quit_layout->addStretch(400);
    quit_layout->addWidget(but_quit, Qt::AlignRight);

    //Horizontal layout for icon
    QHBoxLayout *icon_layout = new QHBoxLayout;
    icon_layout->addStretch(100);
    icon_layout->addWidget(lab_icon);
    icon_layout->addStretch(100);

    //Vertical layout for whole window
    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->setSpacing(10);
    main_layout->addLayout(icon_layout);
    main_layout->addLayout(title_layout, Qt::AlignCenter);
    main_layout->addLayout(grid_layout, Qt::AlignCenter);
    main_layout->addLayout(quit_layout);

    // Set layout in QWidget
    QWidget *window = new QWidget();
    window->setLayout(main_layout);
    this->setWindowIcon(QIcon("TheLexiconGlove.png"));
    window->setWindowTitle("The Lexicon Glove");

    // Set QWidget as the central layout of the main window
    setCentralWidget(window);

    connect(but_mon, &QPushButton::clicked, 
            this, [this](){this->monitor_button_clicked();});


    connect(but_interpret, &QPushButton::clicked,
            this, [this](){this->interpretButtonClicked();});

    connect(but_train, &QPushButton::clicked,
            this, [this](){this->trainButtonClicked();});

    // connect(but_quit, SIGNAL (clicked()),
    //         this, SLOT (but_quit_clicked()));

    connect(but_quit, &QPushButton::clicked,
             this, [this](){this->close();} );



    trainWindow = new TrainWindow();
    trainWindow->setWindowTitle("Training Mode");
    trainWindow->startTimer(1000);
    
    
    cppSampleTimer = new SampleTimer();


    monitorWindow = new MonitorWindow(NUMBER_OF_PLOT_SAMPLES);

    connect(cppSampleTimer, &SampleTimer::timeoutsignal,
           this, [this](){this->newDataEvent();});

    cppSampleTimer->start(DATA_SAMPLE_INTERVAL);

}

void MainWindow::createFilters(){
    // accelFilterBank = new FilterBank(NUMBER_OF_FILTERS, ORDER_OF_FILTERS, SAMPLE_RATE, filterCuttoffFreqs);
    // gyroFilterBank  = new FilterBank(NUMBER_OF_FILTERS, ORDER_OF_FILTERS, SAMPLE_RATE, filterCuttoffFreqs);
    // fingerFilterBank= new FilterBank(NUMBER_OF_FILTERS, ORDER_OF_FILTERS, SAMPLE_RATE, filterCuttoffFreqs);
    // accelFilterBank ->setup();
    // gyroFilterBank  ->setup();
    // fingerFilterBank->setup();

}

void MainWindow::newDataEvent(){

    int16_t* allData = cppSampleTimer->getSensorValues();

    sampleacc[0][0]   =allData[0];
    sampleacc[1][0]   =allData[1];
    sampleacc[2][0]   =allData[2];

    samplegyro[0][0]  =allData[3];
    samplegyro[1][0]  =allData[4];
    samplegyro[2][0]  =allData[5];

    samplefinger[0][0]=allData[6];
    samplefinger[1][0]=allData[7];
    samplefinger[2][0]=allData[8];
    samplefinger[3][0]=allData[9];
    samplefinger[4][0]=allData[10];

    if (monitorWindow->isVisible()){
        QtConcurrent::run([this]() {
            monitorWindow->plotAcc(this->sampleacc);
            monitorWindow->plotGyro(this->samplegyro);
            monitorWindow->plotFinger(this->samplefinger);
        });
    }
}

void MainWindow::timerEvent(){
    /* 
        Read MPU6050 and ADCs
    */
    //for now, create fake data

    // double samplefinger[5][1];
    // double sampleacc[3][1];
    
    int16_t in = 5 * sin(M_PI * count/50.0);
    ++count;
    for (size_t i=0; i<5;i++){
        for (size_t j=0;j<1;j++){
            samplefinger[i][j]= in/(i+1);
        }
    }
    for (size_t i=0; i<3;i++){
        for (size_t j=0;j<1;j++){ 
            sampleacc[i][j]= in/(i+1);
            samplegyro[i][j]= in/(i+1);
        }
    }
    // accelFilterBank->filter(sampleacc[0][0]);
    // gyroFilterBank->filter(sampleacc[0][0]);
    // fingerFilterBank->filter(samplefinger[0][0]);

    // printf("EMIT outside\n");
    if (monitorWindow->isVisible()){
        QtConcurrent::run([this]() {
            monitorWindow->plotAcc(this->sampleacc);
            monitorWindow->plotGyro(this->samplegyro);
            monitorWindow->plotFinger(this->samplefinger);
        });
    }





}

MainWindow::~MainWindow(){
}

void MainWindow::but_quit_clicked(){
    this->close();
}

void MainWindow::monitor_button_clicked(){
    monitorWindow = new MonitorWindow(NUMBER_OF_PLOT_SAMPLES);
    monitorWindow->setAttribute(Qt::WA_DeleteOnClose);
    monitorWindow->setWindowTitle("Monitor");
    moitorRefreshtimer = new QTimer(monitorWindow);
    connect(moitorRefreshtimer, &QTimer::timeout,
            monitorWindow, [this](){monitorWindow->drawPlots();});
    moitorRefreshtimer->start(MONITOR_REFRESH_RATE);
    monitorWindow->show();
}

void MainWindow::trainButtonClicked(){
    trainWindow->show();
}

void MainWindow::interpretButtonClicked(){
    interpretWindow = new InterpretWindow();
    interpretWindow->setAttribute(Qt::WA_DeleteOnClose);
    interpretWindow->setWindowTitle("Interpret Mode");
    windowtimer = new QTimer(interpretWindow);
    connect(windowtimer, SIGNAL(timeout()),interpretWindow, SLOT(timerEvent()));
    windowtimer->start(1000);
    // connect(interpretWindow, SIGNAL(emitClose()),this, SLOT(interpretHome()));
    interpretWindow->show();
}

void MainWindow::interpretHome(){

}

