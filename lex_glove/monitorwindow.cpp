#include "monitorwindow.h"

MonitorWindow::MonitorWindow(QDialog *parent) :
    QDialog(parent)
{
}

MonitorWindow::~MonitorWindow()
{
    delete window();
}
