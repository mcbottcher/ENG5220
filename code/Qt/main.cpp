#include <MonitorWindow.h>

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// create the window
	MonitorWindow window;
	window.showMaximized();

	// call the window.timerEvent function every 40 ms
	window.startTimer(40);

	// execute the application
	return app.exec();
}