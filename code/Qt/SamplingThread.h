#include "CppTimer.h"


#include <QThread>
#include <QObject>


class SamplingThread : public QObject, public CppTimer  {

    Q_OBJECT

public:
    void timerEvent(){
        emit timeoutsignal();
    }


signals:
    void timeoutsignal();

};