#ifndef QLED_H
#define	QLED_H
#include <QFrame>
#include <QColor>

class QLed : public QFrame {
    Q_OBJECT
public:
    QLed(){
        this->setMinimumSize(12, 12);
        this->setAutoFillBackground(true);
        this->setFrameShape(QFrame::StyledPanel);
        this->setFrameShadow(QFrame::Sunken);
        QPalette p = this->palette();
        p.setColor(QPalette::Window, Qt::red);
        this->setPalette(p);
    };
    void setState(const QColor &color){
        QPalette p = this->palette();
        p.setColor(QPalette::Window, color);
        this->setPalette(p);
    };
    virtual ~QLed(){}
private:

};

#endif	/* QLED_H */
