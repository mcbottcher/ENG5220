TEMPLATE = app
TARGET = lexicon_glove

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    monitorwindow.cpp

HEADERS += \
    mainwindow.h \
    monitorwindow.h

FORMS +=