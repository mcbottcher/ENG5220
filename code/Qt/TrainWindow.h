#ifndef TRAINWINDOW_H
#define TRAINWINDOW_H

#include "config.h"

#include <QBoxLayout>
#include <QColor>
#include <QCheckBox>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QGroupBox>
#include <QTimer>
#include "QLed.h"

#include <stdio.h>
#include <fstream>

#define NUMBER_OF_REPETITIONS 20

typedef enum trainingState_t{
    STATE_START,
    STATE_COUNTDOWN_3,
    STATE_COUNTDOWN_2,
    STATE_COUNTDOWN_1,
    STATE_GO,
    STATE_STOP,
    STATE_FINISHED
}trainingState_t;

class TrainWindow : public QWidget{
    Q_OBJECT

private:

    int gesture_count = 0;
    QLineEdit *wordInput;
    QLabel *inputLabel, *statusText, *timerText; 
    QPushButton *wordTrain, *homeButton;

    QLed *led[10];
    QGroupBox *inputGroup, *trainGroup;

    QVBoxLayout *mainLayout;
    QHBoxLayout *homeLayout;
    QHBoxLayout *lightBox;

    QGridLayout *inputLayout, *trainLayout, *ledLayout;

    QTimer *timer;

    trainingState_t currentState = STATE_START;
    QString temp;
    void trainingDataLoop();
    
    void saveMovement();
    int sampleCount = 0;
    
    int16_t* sensorDataptr;
    
    std::ofstream myfile;
	QString filename; 
    float movementData[11][NUMBER_OF_BUFFER_ELEMENTS];

public:
    TrainWindow(int16_t* dataPtr);
    ~TrainWindow();

    void handle_samples();

public slots:
    void closeWindow();
    void data_aq_state_machine();

signals:
    void startSampling_sig();
    void stopSampling_sig();
  
};
#endif // TRAINWINDOW_H

