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
#include <QPlainTextEdit>
#include <QTextToSpeech>

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
	
    QPushButton  *homeButton, *clearButton;
    QLabel  *predictedWordBox;
    QPlainTextEdit  *outputWeightBox;

    QCheckBox    *soundCheckBox;
    
    QTimer *updateWeightsTimer;


	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QHBoxLayout  *soundLayout, *homeLayout;  // vertical layout
    QVBoxLayout  *textLayout;
    
    QVBoxLayout  *vPlotLayout;  
    QHBoxLayout  *hPlotLayout;
	QVBoxLayout  *mainLayout;  

    QVBoxLayout *checkAccLayout, *checkGyroLayout, *checkFingerLayout;
    QHBoxLayout *accLayout, *gyroLayout, *fingerLayout;

    QTextToSpeech *speech;

    NeuralNet *predictor;
    QString weights;

    void predict();
    
    // int16_t* sensorValuesPtr;

    int number_of_net_outputs;
    
    char** net_output_words;

    float normalised_samples[11];
    uint_fast8_t max_index;
    float max;
    float outputweight;

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
    

};

#endif // INTERPRETWINDOW_H
