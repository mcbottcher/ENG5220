#ifndef INTERPRETWINDOW_H
#define INTERPRETWINDOW_H


#include <QBoxLayout>
#include <QColor>
#include <QCheckBox>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QFont>
#include <QTimer>
#include <QTextToSpeech>
#include <QVBoxLayout>
#include <QProgressBar>

#include <stdio.h>
#include <iostream>

#include "../neuralnet_predict/NeuralNet.h"

// class definition 'MonitorWindow'
class InterpretWindow : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

// internal variables for the window class

private:

    int16_t* sensorValuesPtr;

  
    QLabel *loudspeakerIcon;
	
    QPushButton  *homeButton;
    QLabel  *predictedWordBox;

    QCheckBox    *soundCheckBox;
    QProgressBar *outputWeightBars;
    
    QTimer *updateWeightsTimer;


	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QHBoxLayout  *soundLayout, *homeLayout;  // vertical layout
    QVBoxLayout  *textLayout, *weightsLayout;
    
    QVBoxLayout  *vPlotLayout;  
    QHBoxLayout  *hPlotLayout;
	QVBoxLayout  *mainLayout;  

    QVBoxLayout *checkAccLayout, *checkGyroLayout, *checkFingerLayout;
    QHBoxLayout *accLayout, *gyroLayout, *fingerLayout;

    QTextToSpeech *speech;

    NeuralNet *predictor;
    QString weights, lastwordsaid;

    void predict();

    int number_of_net_outputs;
    
    char** net_output_words;

    float normalised_samples[11];
    uint_fast8_t max_index;
    float max;
    
    float* outputWeights;

public:

	InterpretWindow(int16_t* sensorValuesPtr); // default constructor - called when a Window is declared without arguments
	~InterpretWindow();
    void sayWords();

signals:
    void emitClose();
    //void startSampling_sig();
    void stopSampling_sig();

public slots:
    void closeWindow();
    void handleSamples();
    void updateWindow();
    void updateWeights();

};

#endif // INTERPRETWINDOW_H
