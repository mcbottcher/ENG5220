#include "InterpretWindow.h"

InterpretWindow::InterpretWindow(int16_t* sensorValuesPtr) :
        sensorValuesPtr(sensorValuesPtr){

    predictor = new NeuralNet();
    number_of_net_outputs = predictor->get_number_of_outputs();
    
    net_output_words = new char* [number_of_net_outputs];
    
    outputWeightBars = new QProgressBar[number_of_net_outputs];
    weightsLayout = new QVBoxLayout;
    
    outputWeights = new float[number_of_net_outputs];
    
    std::ifstream file1;
    file1.open("Qt/outputMap.txt");
    
    std::string temp;
    
    for(int i=0; i<number_of_net_outputs; i++){
        std::getline(file1, temp);
        net_output_words[i] = new char [temp.length()];
        strcpy(net_output_words[i], temp.c_str());
    }
    
    file1.close();
    
    speakerTimer = new QTimer(this);
    connect(speakerTimer, &QTimer::timeout, this, &InterpretWindow::speaker);
    lastwordsaid = " ";
    // speakerTimer->start(100);

    for(int i=0; i<number_of_net_outputs; i++){
        weightsLayout->addWidget(&outputWeightBars[i], Qt::AlignCenter);
        outputWeightBars[i].setTextVisible(true);
        outputWeightBars[i].setFormat(QString(net_output_words[i]));
    }
   
    updateWeightsTimer = new QTimer(this);
    connect(updateWeightsTimer, &QTimer::timeout, [this](){this->updateWeights();});
    updateWeightsTimer->start(100);
    
    homeButton = new QPushButton("Home");
    connect(homeButton, &QPushButton::clicked, [this](){this->closeWindow();});

    soundCheckBox = new QCheckBox();
    // soundCheckBox->setChecked(true);
    QPixmap pix("../images/Speaker_Icon.png");
    loudspeakerIcon = new QLabel("Test", this);
    loudspeakerIcon->setPixmap(pix.scaled(
        loudspeakerIcon->width(),
        loudspeakerIcon->height(),
        Qt::KeepAspectRatio));

    connect(soundCheckBox, &QCheckBox::stateChanged, [this](){
        soundCheckBox->isChecked() ? speakerTimer->start(100) : speakerTimer->stop();
        });
    soundCheckBox->setChecked(true);

    soundLayout = new QHBoxLayout();
    soundLayout->addStretch(100);
    soundLayout->addWidget(soundCheckBox);
    soundLayout->addWidget(loudspeakerIcon, Qt::AlignCenter);
    soundLayout->addStretch(100);
    
    homeLayout = new QHBoxLayout();
    homeLayout->addStretch(100);
    homeLayout->addWidget(homeButton, Qt::AlignCenter);
    homeLayout->addStretch(100);

    predictedWordBox = new QLabel("Prediction",this);
   
    textLayout = new QVBoxLayout();
    textLayout->addWidget(predictedWordBox, Qt::AlignCenter);
    textLayout->addLayout(weightsLayout, Qt::AlignCenter);

    mainLayout  = new QVBoxLayout();
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
    //emit stopSampling_sig();
    delete predictor;
    delete[] net_output_words;
    delete[] outputWeights;
    delete[] outputWeightBars;
}

void InterpretWindow::closeWindow(){
    speakerTimer->stop();
    emit emitClose();

}

void InterpretWindow::handleSamples(){

    //need to be converted to floats
    // float normalised_samples[11];
    for(uint_fast8_t i=0; i<6; i++){
        //for the accell/gyro
        normalised_samples[i] = (sensorValuesPtr[i]/32768.0);
    }
    for(uint_fast8_t i=6; i<11; i++){
        //for the fingers
        normalised_samples[i] = (sensorValuesPtr[i]/4096.0) - 0.5;
    }
    
    predictor->insertSamples(normalised_samples);
    
    fdeep::tensor result = predictor->predict();
    
    max = 0;
    max_index = 0;
    for(uint_fast8_t i=0; i<number_of_net_outputs; i++){
        
        outputWeights[i] = result.get(fdeep::tensor_pos(i));
        
        if(outputWeights[i]>max){
            max = outputWeights[i];
            max_index = i;
        }

    }
    
    // outputWeightBox->setPlainText(weights);
    // predictedWordBox->clear();
    predictedWordBox->setText(QString(net_output_words[max_index]));
    
}

void InterpretWindow::predict(){

    //std::cout << "predicting values" << std::endl;
    //predictor->predict();

}

void InterpretWindow::updateWeights(){
    
    for(int i=0; i<number_of_net_outputs; i++){
        outputWeightBars[i].setValue(int(outputWeights[i]*100));
    }

}


//used for outputting the voice...
//speech->say(textBox->toPlainText());

void InterpretWindow::speaker(){
    // outputWeightBox->setPlainText(weights);

    // if ((soundCheckBox->isChecked())&&(lastwordsaid != predictedWordBox->text())){
    if (lastwordsaid != predictedWordBox->text()){
        speech->say(predictedWordBox->text());
        lastwordsaid = predictedWordBox->text();
    }
}



