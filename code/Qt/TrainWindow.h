#ifndef TRAINWINDOW_H
#define TRAINWINDOW_H

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

    int count = 0;
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

    trainingState_t currentState;

    void trainingDataLoop();

public:
    TrainWindow();
    ~TrainWindow();


public slots:
    void closeWindow();
    //void updateTimer();
    void data_aq_state_machine();


};
#endif // TRAINWINDOW_H
