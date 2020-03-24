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

    void trainingDataLoop();

public:
    TrainWindow();
    ~TrainWindow();

    void data_aq_complete();

public slots:
    void closeWindow();
    void data_aq_state_machine();

signals:
    void mysignal();
    void openfile_sig();
    void closefile_sig();

};
#endif // TRAINWINDOW_H
