#ifndef MONITORWINDOW_H
#define MONITORWINDOW_H

#include <QDialog>

class MonitorWindow : public QDialog {

    Q_OBJECT

public:
    explicit MonitorWindow(QDialog *parent = nullptr);
    ~MonitorWindow();


};


#endif // MONITORWINDOW_H
