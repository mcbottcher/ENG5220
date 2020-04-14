TEMPLATE = app
TARGET = monitorwindow

CONFIG += qt warn_on debug


OBJECTS_DIR=build_files 
MOC_DIR=build_files 


QT += core gui  

greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lqwt-qt5 -lm -liir -lrt
lessThan(QT_MAJOR_VERSION, 5): LIBS += -lqwt -lm -liir  -lrt
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    ../../Qt/monitorwindow.cpp    \
    ../../FilterBank.cpp \
    ../../cppTimer/CppTimer.cpp \


HEADERS += \
    ../../Qt/monitorwindow.h  \
    ../../FilterBank.h \
    ../../cppTimer/CppTimer.h \


FORMS +=

   
INCLUDEPATH += ../usr/include/ \