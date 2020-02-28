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


#include <stdio.h>


// class definition 'MonitorWindow'
class InterpretWindow : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

// internal variables for the window class

private:
    int count=0;

    QFont titleFont;
    QLabel *titleText, *loudspeakerIcon;
	
    QPushButton  *homeButton, *wrongButton, *clearButton;
    QPlainTextEdit *textBox;

    QCheckBox    *soundCheckBox;
    


	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QHBoxLayout  *titleLayout, *soundLayout, *homeLayout;  // vertical layout
    
    QVBoxLayout  *vPlotLayout;  
    QHBoxLayout  *hPlotLayout;
	QVBoxLayout  *mainLayout;  

    QVBoxLayout *checkAccLayout, *checkGyroLayout, *checkFingerLayout;
    QHBoxLayout *accLayout, *gyroLayout, *fingerLayout;




public:

	InterpretWindow(); // default constructor - called when a Window is declared without arguments
	~InterpretWindow();
    void timerEvent( QTimerEvent * );

public slots:

    // void closeWindow();
    void wrongButtonClicked();
    void clearTextClicked();

};

#endif // INTERPRETWINDOW_H