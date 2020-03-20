#ifndef QLED_H
#define	QLED_H
#include <QFrame>
#include <QColor>

//!  QLed Class
/*!
    Class to draw small coloured squares that can change colour using the setState method.
*/
class QLed : public QFrame {
    Q_OBJECT
public:
    QLed(){
        this->setMinimumSize(12, 12);
        this->setAutoFillBackground(true);
        this->setFrameShape(QFrame::StyledPanel);
        this->setFrameShadow(QFrame::Sunken);
        setState(Qt::red); //set default starting colour to red.
        // QPalette p = this->palette();
        // p.setColor(QPalette::Window, Qt::red); 
        // this->setPalette(p);
    };



    //! setState method.
    /*! method to set the colour of the LED.
        \param colour colour argument to change the QLed colour (i.e Qt::red, Qt::green).
    */
    void setState(const QColor &colour){
        QPalette p = this->palette();
        p.setColor(QPalette::Window, colour);
        this->setPalette(p);
    };
    virtual ~QLed(){}
private:

};

#endif	/* QLED_H */
