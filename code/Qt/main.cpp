#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 MainWindow home_page;
 home_page.show();

 return app.exec();
}