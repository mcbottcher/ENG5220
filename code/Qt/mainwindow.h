#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MonitorWindow.h"
#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QToolButton>
//#include <QFont>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    size_t plotBufferSize = 10;
    MonitorWindow *monitor_window;
    QPixmap *logo_image;
    QFont title_font;
    QLabel *title_text, *logo, *lab_train, *lab_interpret, *lab_mon, *lab_icon;
    QPushButton *but_train, *but_interpret, *but_mon, *but_quit;
    //QToolButton *logo_icon;
    //QVBoxLayout main_layout;

private slots:
    void monitor_button_clicked();
    void but_quit_clicked();

};

#endif // MAINWINDOW_H
