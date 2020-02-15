#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QPixmap pix("TheLexiconGlove.png");
    //QLabel icon_label;
    //icon_label.setPixmap(pix);
    //icon_label.setText("Test");
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

    //Vertical layout for whole window
    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->setSpacing(10);
    main_layout->addWidget(lab_icon);
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

    connect(but_mon, SIGNAL (clicked()),
            this, SLOT (monitor_button_clicked()));

    connect(but_quit, SIGNAL (clicked()),
            this, SLOT (but_quit_clicked()));


    monitor_window = new MonitorWindow(plotBufferSize);
    monitor_window->startTimer(80);
}

MainWindow::~MainWindow(){
    delete monitor_window;
}

void MainWindow::but_quit_clicked(){
    this->close();
}

void MainWindow::monitor_button_clicked(){
    monitor_window->show();
}

