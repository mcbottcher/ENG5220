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


#include <stdio.h>

class TrainWindow : public QWidget{
    Q_OBJECT

private:

    int count = 0;
    QLineEdit *wordInput;
    QLabel *inputLabel, *statusText, *timerText; 
    QPushButton *wordTrain, *homeButton;

    QGroupBox *inputGroup, *trainGroup;

    QVBoxLayout *mainLayout;
    QHBoxLayout *homeLayout;

    QGridLayout *inputLayout, *trainLayout;

    QTimer *timer;

public:
    TrainWindow();
    ~TrainWindow();


public slots:
    void closeWindow();
    void updateTimer();


};

#endif // TRAINWINDOW_H