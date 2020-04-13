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

/** 
* Class representing a window where movement interpretation is performed. Data is sampled
* and passed through the neural network, and the predicted output displayed on the screen.
*/
class InterpretWindow : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

// internal variables for the window class

private:

    /** Pointer to the new values from sampling the sensors */
    int16_t* sensorValuesPtr;

    QLabel *loudspeakerIcon;
	
    QPushButton  *homeButton;
    QLabel  *predictedWordBox;

    QCheckBox    *soundCheckBox;
    QProgressBar *outputWeightBars;
    
    QTimer *updateWeightsTimer, *speakerTimer;


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

    /** Function to run the data through the neural network and produce a prediction */
    void predict();

    /** Variable to save the number of network outputs */
    int number_of_net_outputs;
    
    /** Pointer to an array containing the words corresponding to each network output */
    char** net_output_words;

    /** Array to store samples after they have been normailsed for the network */
    float normalised_samples[11];
    /** Stores the index of the network output with the highest predicted weight */
    uint_fast8_t max_index;
    /** Stores the value of the network output with the highest predicted weight */
    float max;
    
    /** Pointer to access the output weights array */
    float* outputWeights;

public:
    
    /**
    * Class constructor. Is responsible for setting up the interpret window
    * @param sensorValuesPtr is a pointer to the buffer where the newly sampled sensor values
    * are stored
    */
	InterpretWindow(int16_t* sensorValuesPtr); // default constructor - called when a Window is declared without arguments
	~InterpretWindow();
	
	/** Currently not implemented */
    void sayWords();

signals:
    /** Signal to signal the main window to close the interpret window */
    void emitClose();
    //void startSampling_sig();
    
    /** Signal to stop sampling in the main window */
    void stopSampling_sig();

public slots:
    
    /** Function to handle proper shutdown of the window */
    void closeWindow();
    /** Function to handle new samples by passing them into the neural net */
    void handleSamples();
    /** Function to handle text2speech functionality */
    void speaker();
    /** Function to update the GUI output weights' values with those of the output from 
    * the neural network 
    */
    void updateWeights();

};

#endif // INTERPRETWINDOW_H
