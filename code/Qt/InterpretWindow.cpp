#include "InterpretWindow.h"




InterpretWindow::InterpretWindow(){

    homeButton = new QPushButton("Home");
    connect(homeButton, &QPushButton::clicked, [this](){this->close();});

    clearButton = new QPushButton("Clear");
    connect(clearButton, &QPushButton::clicked, [this](){outputWeightBox->clear();});

    soundCheckBox = new QCheckBox();
    QPixmap pix("Speaker_Icon.png");
    loudspeakerIcon = new QLabel("Test", this);
    loudspeakerIcon->setPixmap(pix.scaled(
        loudspeakerIcon->width(),
        loudspeakerIcon->height(),
        Qt::KeepAspectRatio));

    soundLayout = new QHBoxLayout;
    soundLayout->addStretch(100);
    soundLayout->addWidget(soundCheckBox);
    soundLayout->addWidget(loudspeakerIcon, Qt::AlignCenter);
    soundLayout->addStretch(100);
    
    homeLayout = new QHBoxLayout;
    homeLayout->addStretch(100);
    homeLayout->addWidget(clearButton, Qt::AlignCenter);
    homeLayout->addWidget(homeButton, Qt::AlignCenter);
    homeLayout->addStretch(100);

    predictedWordBox = new QPlainTextEdit;
    outputWeightBox = new QPlainTextEdit;

    textLayout = new QVBoxLayout;
    textLayout->addWidget(predictedWordBox, Qt::AlignCenter);
    textLayout->addWidget(outputWeightBox, Qt::AlignCenter);

    mainLayout  = new QVBoxLayout;
    mainLayout->addLayout(soundLayout);
    mainLayout->addLayout(textLayout);
    mainLayout->addLayout(homeLayout);
    
    speech = new QTextToSpeech();
    speech->setLocale(QLocale(QLocale::English,QLocale::LatinScript,QLocale::UnitedStates));
    speech->setRate(2);
    speech->setPitch(2);
    speech->setVolume(100);

    setLayout(mainLayout);

}


InterpretWindow::~InterpretWindow(){
    
}

void InterpretWindow::closeWindow(){
    emit emitClose();

}


//used for outputting the voice...
//speech->say(textBox->toPlainText());



