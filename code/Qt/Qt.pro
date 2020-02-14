# Qt project file - qmake uses his to generate a Makefile

QT += core gui

CONFIG += qt warn_on debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt

greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lqwt-qt5 -lm
lessThan(QT_MAJOR_VERSION, 5): LIBS += -lqwt -lm

HEADERS += MonitorWindow.h 

SOURCES += main.cpp MonitorWindow.cpp 