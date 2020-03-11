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



    QFont Font("Arial", 20, QFont::Bold);
    statusText = new QLabel("", this);
    statusText->setFont(Font);

    timerText = new QLabel("", this);
    timerText->setFont(Font);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(1000);

    ledLayout = new QGridLayout;
    for (int i =0; i<10;i++){
        led[i] = new QLed();
        led[i]->setState(Qt::red);
        ledLayout->addWidget(led[i],0,i);
        }
    

    trainGroup = new QGroupBox(tr("Training stuff"));

    trainLayout = new QGridLayout;
    trainLayout->addWidget(statusText, 0, 0);
    trainLayout->addWidget(timerText, 0, 1);
    trainLayout->addLayout(ledLayout,1,0,1,2);
    trainGroup->setLayout(trainLayout);



    homeButton = new QPushButton("Save");
    connect(homeButton, &QPushButton::clicked, [this](){this->closeWindow();});

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
void TrainWindow::trainingDataLoop(){
    for(int i=0;i<10;i++){
        led[i]->setState(Qt::yellow);
        
        led[i]->setState(Qt::green);
    }

}

TrainWindow::~TrainWindow(){
}

void TrainWindow::closeWindow(){
    /// Train the model with the new data
    /// link the outputs to text files


}


void TrainWindow::updateTimer(){
    char buffer [50];
    sprintf (buffer, "%d", count);
    QString number(buffer);
    statusText->setText(number);
    timerText->setText(number);
    ++count;
}

