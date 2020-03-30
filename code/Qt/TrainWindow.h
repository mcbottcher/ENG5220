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
#include <QListWidget>
#include <QDir>
#include <QAbstractItemView>
#include <QMessageBox>
#include "QLed.h"

#include <stdio.h>
#include <fstream>

#define NUMBER_OF_REPETITIONS 20

//! Training State Enum.
/*!
    Used to store the state of the state machine!
    \sa data_aq_state_machine()
*/
typedef enum trainingState{
    STATE_START,
    STATE_COUNTDOWN_3,
    STATE_COUNTDOWN_2,
    STATE_COUNTDOWN_1,
    STATE_GO,
    STATE_STOP,
    STATE_FINISHED
}trainingState_t;

//!  Training Window Class
/*!
    Class to allow easy training of the neural network with given hand actions.
*/
class TrainWindow : public QWidget{
    Q_OBJECT

private:
    //!  Pointer to where the incoming samples are stored.
    /*!   */
    int16_t* sensorDataptr;

    //!  Counter to count the number of gestures that have already been recorded.
    /*!   */
    uint8_t gesture_count = 0;

    //!  LEDs to help show progress of training.
    /*!  \sa QLed() */
    QLed *led[10];
    QGroupBox *inputGroup, *trainGroup, *netGroup;
    QListWidget *movementList;
    QVBoxLayout *mainLayout;
    QGridLayout *homeLayout;
    QHBoxLayout *lightBox;
    QGridLayout *inputLayout, *trainLayout, *ledLayout;
    QLineEdit *wordInput;
    QLabel *inputLabel, *statusText, *timerText; 
    QPushButton *wordTrain, *nettrainButton, *homeButton;

    //!  State machine Qtimer
    /*!   */
    QTimer *timer;

    //!  List of files with training data.
    /*!   */
    QStringList files;

    //!  An Enum of type trainingState.
    /*!   */
    trainingState_t currentState = STATE_START;
    //!  Helper function to change LED colours?
    /*!   */
    void trainingDataLoop();    // depreciated?
    //!  Save movement method
    /*!  helper function to save the captured movement as a CSV File.*/
    void saveMovement();

    //!  Sample Count
    /*!  count how many samples have been recieved. after 20 samples, save the movement!
        \sa saveMovement(), data_aq_state_machine() and stopSampling_sig()*/
    uint8_t sampleCount = 0;
    

    
    std::ofstream myfile;
	QString filename; 
    float movementData[11][NUMBER_OF_BUFFER_ELEMENTS];

public:
    //! Default constructor.
    /*!
        \param dataPtr pointer to where the CppTimer stores the sensor values.
    */
    TrainWindow(int16_t* dataPtr);
    ~TrainWindow();

    //!  Handle Samples method.
    /*!  Method that handles samples as they come in.*/
    void handleSamples();

public slots:
    //!  Slot to startup the Neural network.
    /*!  */
    void startNeuralNet();
    //!  Slot change the state of the state machine.
    /*!  */
    void data_aq_state_machine();
    //!  Slot to safely close the window.
    /*!  */
    void closeWindow();

signals:
    //!  Signal to start the CppTimer.
    /*!  */
    void startSampling_sig();
    //!  Signal to start the CppTimer.
    /*!  */
    void stopSampling_sig();
    //!  Signal to say we have safly closed the window!
    /*!  */
    void emitClose();
  
};
#endif // TRAINWINDOW_H

