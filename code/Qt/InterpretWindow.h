#ifndef INTERPRETWINDOW_H
#define INTERPRETWINDOW_H


#include <QBoxLayout>
#include <QColor>
#include <QCheckBox>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QFont>
#include <QPlainTextEdit>
#include <QTextToSpeech>
#include <QDebug>

#include <stdio.h>


// class definition 'MonitorWindow'
class InterpretWindow : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

// internal variables for the window class

private:
    int count=0;

  
    QLabel *loudspeakerIcon;
	
    QPushButton  *homeButton, *clearButton;
    QPlainTextEdit *predictedWordBox, *outputWeightBox;

    QCheckBox    *soundCheckBox;
    


	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QHBoxLayout  *soundLayout, *homeLayout;  // vertical layout
    QVBoxLayout  *textLayout;
    
    QVBoxLayout  *vPlotLayout;  
    QHBoxLayout  *hPlotLayout;
	QVBoxLayout  *mainLayout;  

    QVBoxLayout *checkAccLayout, *checkGyroLayout, *checkFingerLayout;
    QHBoxLayout *accLayout, *gyroLayout, *fingerLayout;

    QTextToSpeech *speech;



public:

	InterpretWindow(); // default constructor - called when a Window is declared without arguments
	~InterpretWindow();
    void sayWords();

signals:
    void emitClose();

public slots:
    void closeWindow();

};

#endif // INTERPRETWINDOW_H
