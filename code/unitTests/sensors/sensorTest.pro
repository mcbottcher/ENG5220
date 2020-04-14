TEMPLATE = app
TARGET = sensorTest

CONFIG += qt warn_on debug


OBJECTS_DIR=build_files 
MOC_DIR=build_files 


QT += core gui

#greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lqwt-qt5 -lm -liir -lrt
#lessThan(QT_MAJOR_VERSION, 5): LIBS += -lqwt -lm -liir  -lrt
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp    \
    ../../MPU6050/MPU6050.cpp \
    ../../MCP3428/MCP3428.cpp \
    ../../MPU6050/I2Cdev/I2Cdev.cpp \


HEADERS += \
    ../../MPU6050/MPU6050.h \
    ../../MCP3428/MCP3428.h \
    ../../MPU6050/I2Cdev/I2Cdev.h \
    

FORMS +=


