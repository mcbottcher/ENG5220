#include "TrainWindow.h"


TrainWindow::TrainWindow(){
    
    inputGroup = new QGroupBox(tr("Input"));

    inputLabel = new QLabel(tr("Training word:"));
    wordInput = new QLineEdit;
    wordInput->setPlaceholderText("Insert word Here");
    wordInput->setFocus();

    wordTrain = new QPushButton("Train word");

    connect(wordTrain, SIGNAL (released()),this, SLOT (data_aq_state_machine()));

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
    timer->setSingleShot(true);
    
    //so we want the timer to exist
    //make a state machine
    //it outputs depending on the state and updates the state
    

    connect(timer, SIGNAL(timeout()), this, SLOT(data_aq_state_machine()));

    ledLayout = new QGridLayout;
    for (int i =0; i<10;i++){
        led[i] = new QLed();
        led[i]->setState(Qt::red);
        ledLayout->addWidget(led[i],0,i);
        }
    

    trainGroup = new QGroupBox(tr("Data Aquisition"));

    trainLayout = new QGridLayout;
    trainLayout->addWidget(statusText, 0, 0);
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
    
    
    currentState = STATE_START;

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

/*
void TrainWindow::updateTimer(){
    char buffer [50];
    sprintf (buffer, "%d", count);
    QString number(buffer);
    statusText->setText(number);
    ++count;
}
*/

void TrainWindow::data_aq_state_machine(){
    
    switch(currentState){
        case STATE_START:
            statusText->setText("STARTING");
            timer->start(1000); //time in ms
            currentState = STATE_COUNTDOWN_3;
            break;
        case STATE_COUNTDOWN_3:
            statusText->setText("3 ...");
            timer->start(1000); //time in ms
            currentState = STATE_COUNTDOWN_2;
            break;
        case STATE_COUNTDOWN_2:
            statusText->setText("2 ...");
            timer->start(1000); //time in ms
            currentState = STATE_COUNTDOWN_1;
            break;
        case STATE_COUNTDOWN_1:
            statusText->setText("1 ...");
            timer->start(1000); //time in ms
            currentState = STATE_GO;
            break;
        case STATE_GO:
            statusText->setText("GO!");
            timer->start(2000); //time in ms
            currentState = STATE_STOP;
            break;
        case STATE_STOP:
            statusText->setText("STOP!");
            timer->start(1000); //time in ms
            currentState = STATE_FINISHED;
            break;
        case STATE_FINISHED:
            statusText->setText("FINISHED");
            currentState = STATE_START;
            break;
    
    }
}


