#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 MainWindow home_page;
 home_page.show();

 return app.exec();
}
