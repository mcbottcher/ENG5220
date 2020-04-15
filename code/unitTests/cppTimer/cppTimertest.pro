TEMPLATE = app
TARGET = cppTimerTest


OBJECTS_DIR=build_files 
MOC_DIR=build_files 

LIBS += -lrt

SOURCES += \
    main.cpp    \
    ../../cppTimer/CppTimer.cpp \

HEADERS += \
    ../../cppTimer/CppTimer.h \
    

FORMS +=
