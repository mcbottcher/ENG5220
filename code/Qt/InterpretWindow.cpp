#include "InterpretWindow.h"

InterpretWindow::InterpretWindow(int16_t* sensorValues){

    sensorValuesPtr = sensorValues;

    predictor = new NeuralNet;
    number_of_net_outputs = predictor->get_number_of_outputs();
    
    net_output_words = new char* [number_of_net_outputs];
    
    
    
    std::ifstream file1;
    file1.open("outputMap.txt");
    
    std::string temp;
    
    for(int i=0; i<number_of_net_outputs; i++){
        std::getline(file1, temp);
        net_output_words[i] = new char [temp.length()];
        strcpy(net_output_words[i], temp.c_str());
    }
    
    file1.close();
    
    
    
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
    
    //emit startSampling_sig();

}


InterpretWindow::~InterpretWindow(){
    emit stopSampling_sig();
    delete predictor;
    for(int i=0; i<number_of_net_outputs;i++){
        delete net_output_words[i];
    }
    delete net_output_words;
}

void InterpretWindow::closeWindow(){
    emit emitClose();

}

void InterpretWindow::handleSamples(){

    //need to be converted to floats
    float normalised_samples[11];
    for(int i=0; i<6; i++){
        //for the accell/gyro
        normalised_samples[i] = (sensorValuesPtr[i]/32768.0);
    }
    for(int i=6; i<11; i++){
        //for the fingers
        normalised_samples[i] = (sensorValuesPtr[i]/4096.0) - 0.5;
    }
    
    predictor->insertSamples(normalised_samples);
    
    fdeep::tensor result = predictor->predict();
    
    outputWeightBox->clear();
    
    float max = 0;
    int max_index = 0;
    float outputweight; 
    
    for(int i=0; i<number_of_net_outputs; i++){
        
        outputweight = result.get(fdeep::tensor_pos(i));
        
        if(outputweight>max){
            max = outputweight;
            max_index = i;
        }
        
        outputWeightBox->appendPlainText(QString::number(outputweight));
    
    }
    
   
    predictedWordBox->clear();
    QString predictedWord(net_output_words[max_index]);
    predictedWordBox->appendPlainText(predictedWord);
    
}

void InterpretWindow::predict(){

    //std::cout << "predicting values" << std::endl;
    //predictor->predict();

}

//used for outputting the voice...
//speech->say(textBox->toPlainText());



