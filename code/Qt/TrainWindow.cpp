#include "TrainWindow.h"


TrainWindow::TrainWindow(int16_t* dataPtr):
    sensorDataptr(dataPtr){
    

    for(int i=0; i<11; i++){
        sensorDataptr[i] = i;
    }
    
    inputGroup = new QGroupBox(tr("Input"));

    inputLabel = new QLabel(tr("Training word:"));
    wordInput = new QLineEdit;
    wordInput->setPlaceholderText("Insert word Here");
    wordInput->setFocus();

    wordTrain = new QPushButton("Train word");

    connect(wordTrain, &QPushButton::released, this, &TrainWindow::data_aq_state_machine);

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
    
    connect(timer, &QTimer::timeout, this, &TrainWindow::data_aq_state_machine);

    //setup LEDs
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


    netGroup = new QGroupBox(tr("Neural Network"));

    nettrainButton = new QPushButton("Run Network");
    connect(nettrainButton, &QPushButton::clicked, [this](){this->startNeuralNet();});

    movementList = new QListWidget();
    movementList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QDir directory;
    QStringList files = directory.entryList(QStringList() << "*.csv", QDir::Files);
    movementList->addItems(files);

    homeButton = new QPushButton("Home");
    connect(homeButton, &QPushButton::clicked, [this](){this->closeWindow();});


    homeLayout = new QGridLayout;
    homeLayout->addWidget(movementList, 0, 0);
    homeLayout->addWidget(nettrainButton, 0, 1);
    netGroup->setLayout(homeLayout);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(trainGroup);
    mainLayout->addWidget(netGroup);
    mainLayout->addWidget(homeButton);
    
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

void TrainWindow::startNeuralNet(){
    
    QList<QListWidgetItem *> selected_movements = movementList->selectedItems();
    if (selected_movements.size()<2){
        QMessageBox msg;
        msg.setText("Not enough movements selected.");
        msg.setInformativeText("At least two movements must be selected.");
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    
    std::string command = "python3 neuralNet.py ";
    
    for(int i=0; i<selected_movements.size(); i++){
        command += (selected_movements[i]->text()).toStdString();
        command += " ";
    }

    command += "&";
    QMessageBox msg1;
    msg1.setText("Training neural network.");
    msg1.setInformativeText("This may take a while...");
    msg1.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msg1.setDefaultButton(QMessageBox::Ok);

    if (msg1.exec()==QMessageBox::Ok){
        system(command.c_str());
    }
}



void TrainWindow::data_aq_state_machine(){
    
    switch(currentState){
        case STATE_START:
            statusText->setText("STARTING");
            gesture_count = 1;
            for (int i =0; i<10;i++){
                led[i]->setState(Qt::red);
            }
            
            filename = wordInput->text();
            myfile.open (filename.toStdString() + ".csv"); 
            
            sampleCount = 0;
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
            emit startSampling_sig();
            currentState = STATE_STOP;
            break;
            
        case STATE_STOP:
        
            statusText->setText("STOP!");
            
            saveMovement();
            
            for (int i =0; i<(gesture_count*10/NUMBER_OF_REPETITIONS); i++){
                led[i]->setState(Qt::green);
                }
                
            if(++gesture_count > NUMBER_OF_REPETITIONS){
                currentState = STATE_FINISHED;
                timer->start(1000); //time in ms
            }
            else{
                currentState = STATE_COUNTDOWN_3;
                timer->start(3000); //time in ms
            }
            break;
            
        case STATE_FINISHED:
            myfile.close();
            statusText->setText("FINISHED");
            movementList->addItem(QString(wordInput->text()+ ".csv"));
            currentState = STATE_START;
            break;
    
    }
}

void TrainWindow::handleSamples(){
    
    if (currentState !=STATE_START){
        for(uint_fast8_t i=0; i<11; i++){
            movementData[i][sampleCount] = sensorDataptr[i];
        }
    
        sampleCount++;
        
        if(sampleCount == 20){
            sampleCount = 0;
            //stop the cpptimer with a signal
            emit stopSampling_sig();
            //write row to csv file
            saveMovement();
            //goto the next state
            data_aq_state_machine();
        }
        else{
            //nop
        }
    }
      
}

void TrainWindow::saveMovement(){
    
	for(uint_fast8_t j=0; j< 11;j++){

			for(int k=0; k< NUMBER_OF_BUFFER_ELEMENTS;k++){
				myfile << movementData[j][k] << ",";
			}
		}
		myfile << "\n";
}

void TrainWindow::closeWindow(){

    timer->stop();
    emit stopSampling_sig();
    if(myfile.is_open()){
        myfile.close();
    }
    currentState = STATE_START;

    this->hide();
    emit emitClose();
}
