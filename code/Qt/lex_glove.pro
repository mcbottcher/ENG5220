TEMPLATE = app
TARGET = lexicon_glove

CONFIG += qt warn_on debug

QT += core gui \
    texttospeech 



greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lqwt-qt5 -lm -liir 
lessThan(QT_MAJOR_VERSION, 5): LIBS += -lqwt -lm -liir 
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    MonitorWindow.cpp \
    InterpretWindow.cpp \
    TrainWindow.cpp \
    ../FilterBank.cpp

HEADERS += \
    mainwindow.h \
    MonitorWindow.h \
    InterpretWindow.h \
    TrainWindow.h \
    QLed.h \
    ../FilterBank.h \
    
    

FORMS +=

INCLUDEPATH += ../usr/include/

