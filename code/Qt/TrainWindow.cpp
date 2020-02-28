#include "TrainWindow.h"


TrainWindow::TrainWindow(){
    
    inputGroup = new QGroupBox(tr("Input"));

    inputLabel = new QLabel(tr("Training word:"));
    wordInput = new QLineEdit;
    wordInput->setPlaceholderText("Insert word Here");
    wordInput->setFocus();

    wordTrain = new QPushButton("Train word");

    inputLayout = new QGridLayout;
    inputLayout->addWidget(inputLabel, 0, 0);
    inputLayout->addWidget(wordInput, 1, 0, 1, 2);
    inputLayout->addWidget(wordTrain, 1, 3);
    inputGroup->setLayout(inputLayout);


    trainGroup = new QGroupBox(tr("Training stuff"));

    QFont Font("Arial", 20, QFont::Bold);
    statusText = new QLabel("", this);
    statusText->setFont(Font);

    timerText = new QLabel("", this);
    timerText->setFont(Font);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(1000);

    lights = new TrafficLightWidget*[10];
   


    lightBox = new QHBoxLayout(this);
    for (int i =0; i<10; i++){
        lightBox->addWidget(lights[i])
    }

    trainLayout = new QGridLayout;
    trainLayout->addWidget(statusText, 0, 0);
    trainLayout->addWidget(timerText, 0, 1);
    trainLayout->addLayout(lightBox);
    trainGroup->setLayout(trainLayout);



    homeButton = new QPushButton("Home");
    connect(homeButton, &QPushButton::clicked, [this](){this->close();});

    homeLayout = new QHBoxLayout;
    homeLayout->addStretch(100);
    homeLayout->addWidget(homeButton,  Qt::AlignCenter);
    homeLayout->addStretch(100);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(trainGroup);
    mainLayout->addLayout(homeLayout);


    setLayout(mainLayout);

}

TrainWindow::~TrainWindow(){
}


void TrainWindow::updateTimer(){
    char buffer [50];
    sprintf (buffer, "%d", count);
    QString number(buffer);
    statusText->setText(number);
    timerText->setText(number);
    ++count;
}

