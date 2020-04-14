TEMPLATE = app
TARGET = sensorTest


OBJECTS_DIR=build_files 
MOC_DIR=build_files 


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


