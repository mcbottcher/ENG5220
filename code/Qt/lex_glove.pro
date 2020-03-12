TEMPLATE = app
TARGET = lexicon_glove

CONFIG += qt warn_on debug

QT += core gui \
    texttospeech  \
    concurrent

greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lqwt-qt5 -lm -liir -lrt
lessThan(QT_MAJOR_VERSION, 5): LIBS += -lqwt -lm -liir  -lrt
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    MonitorWindow.cpp \
    InterpretWindow.cpp \
    TrainWindow.cpp \
    SampleTimer.cpp \
    ../FilterBank.cpp \
    ../cppTimer/CppTimer.cpp \
    ../MCP3428/MCP3428.cpp \
    ../MPU6050/MPU6050.cpp \
    ../MPU6050/I2Cdev/I2Cdev.cpp \


HEADERS += \
    mainwindow.h \
    MonitorWindow.h \
    InterpretWindow.h \
    TrainWindow.h \
    QLed.h \
    ../FilterBank.h \
    ../cppTimer/CppTimer.h \
    SampleTimer.h \
    ../MCP3428/MCP3428.h \
    ../MPU6050/MPU6050.h \
    ../MPU6050/I2Cdev/I2Cdev.h \
    

FORMS +=

INCLUDEPATH += ../usr/include/

