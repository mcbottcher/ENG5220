#include "InterpretWindow.h"




InterpretWindow::InterpretWindow(){


    QFont titleFont("Arial", 20, QFont::Bold);
    titleText = new QLabel("", this);
    titleText->setFont(titleFont);

    wrongButton = new QPushButton("Wrong word");
    connect(wrongButton, SIGNAL(clicked()), SLOT(wrongButtonClicked()));

    homeButton = new QPushButton("Home");
    connect(homeButton, &QPushButton::clicked, [this](){this->close();});

    clearButton = new QPushButton("Clear");
    connect(clearButton, &QPushButton::clicked, [this](){textBox->clear();});

    sayButton = new QPushButton("Say words");
    connect(sayButton, &QPushButton::clicked, [this](){this->sayWords();});


    soundCheckBox = new QCheckBox();
    QPixmap pix("Speaker_Icon.png");
    loudspeakerIcon = new QLabel("Test", this);
    loudspeakerIcon->setPixmap(pix.scaled(
        loudspeakerIcon->width(),
        loudspeakerIcon->height(),
        Qt::KeepAspectRatio));

    textBox = new QPlainTextEdit;




    soundLayout = new QHBoxLayout;
    soundLayout->addStretch(100);
    soundLayout->addWidget(soundCheckBox);
    soundLayout->addWidget(loudspeakerIcon, Qt::AlignRight);

    titleLayout = new QHBoxLayout;
    titleLayout->addStretch(100);
    titleLayout->addWidget(titleText);
    titleLayout->addStretch(100);
    titleLayout->addWidget(wrongButton, Qt::AlignRight);

    homeLayout = new QHBoxLayout;
    homeLayout->addStretch(100);
    homeLayout->addWidget(sayButton, Qt::AlignCenter);
    homeLayout->addWidget(clearButton, Qt::AlignCenter);
    homeLayout->addWidget(homeButton, Qt::AlignCenter);
    homeLayout->addStretch(100);

    mainLayout  = new QVBoxLayout;
    mainLayout->addLayout(soundLayout);
    mainLayout->addLayout(titleLayout);
    mainLayout->addWidget(textBox);
    mainLayout->addLayout(homeLayout);
    


    speech = new QTextToSpeech();
    speech->setLocale(QLocale(QLocale::English,QLocale::LatinScript,QLocale::UnitedStates));
    speech->setRate(10);
    speech->setPitch(2);
    speech->setVolume(50);

    setLayout(mainLayout);

}


InterpretWindow::~InterpretWindow(){

}

void InterpretWindow::closeWindow(){
    // this->close();
    emit emitClose();

}

void InterpretWindow::sayWords(){
    speech->say(textBox->toPlainText());
   
}

void InterpretWindow::wrongButtonClicked(){
}


void InterpretWindow::timerEvent(){

    char buffer [50];
    sprintf (buffer, "%d", count);
    QString number(buffer);
    titleText->setText(number);
    ++count;
    speech->say(number);
}