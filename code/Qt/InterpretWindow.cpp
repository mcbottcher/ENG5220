#include "InterpretWindow.h"


InterpretWindow::InterpretWindow(){


    QFont titleFont("Arial", 20, QFont::Bold);
    titleText = new QLabel("", this);
    titleText->setFont(titleFont);

    wrongButton = new QPushButton("Wrong word");
    connect(wrongButton, SIGNAL(clicked()), SLOT(wrongButtonClicked()));

    homeButton = new QPushButton("Home");
    connect(homeButton, SIGNAL(clicked()), SLOT(closeWindow()));

    clearButton = new QPushButton("Clear");
    connect(clearButton, SIGNAL(clicked()), SLOT(clearTextClicked()));


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
    homeLayout->addWidget(clearButton, Qt::AlignCenter);
    homeLayout->addWidget(homeButton, Qt::AlignCenter);
    homeLayout->addStretch(100);

    mainLayout  = new QVBoxLayout;
    mainLayout->addLayout(soundLayout);
    mainLayout->addLayout(titleLayout);
    mainLayout->addWidget(textBox);
    mainLayout->addLayout(homeLayout);

    setLayout(mainLayout);

}

InterpretWindow::~InterpretWindow(){}

void InterpretWindow::closeWindow(){
    this->close();
}

void InterpretWindow::wrongButtonClicked(){
    //system("echo Hello |festival --tts");
}
void InterpretWindow::clearTextClicked(){

}

void InterpretWindow::timerEvent(QTimerEvent *){

    char buffer [50];
    sprintf (buffer, "%d", count);
    QString number(buffer);
    titleText->setText(number);
    ++count;
}