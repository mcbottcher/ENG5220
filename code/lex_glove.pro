TEMPLATE = app
TARGET = lexicon_glove

CONFIG += qt warn_on debug


OBJECTS_DIR=build_files 
MOC_DIR=build_files 


QT += core gui \
    texttospeech  

greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lqwt-qt5 -lm -liir -lrt
lessThan(QT_MAJOR_VERSION, 5): LIBS += -lqwt -lm -liir  -lrt
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    Qt/*.cpp    \
    filters/FilterBank.cpp \
    cppTimer/CppTimer.cpp \
    MCP3428/MCP3428.cpp \
    MPU6050/MPU6050.cpp \
    MPU6050/I2Cdev/I2Cdev.cpp \
    neuralnet_predict/NeuralNet.cpp \


HEADERS += \
    Qt/*.cpp \
    filters/FilterBank.h \
    cppTimer/CppTimer.h \
    MCP3428/MCP3428.h \
    MPU6050/MPU6050.h \
    MPU6050/I2Cdev/I2Cdev.h \
    neuralnet_predict/NeuralNet.h \
    

FORMS +=

INCLUDEPATH += ../usr/include/ \
    ../images/

