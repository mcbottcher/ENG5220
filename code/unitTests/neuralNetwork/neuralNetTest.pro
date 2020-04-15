TEMPLATE = app
TARGET = neuralNetTest


OBJECTS_DIR=build_files 
MOC_DIR=build_files 


SOURCES += \
    main.cpp    \
    ../../neuralnet_predict/NeuralNet.cpp \
    ../../neuralnet_predict/CSVreader.cpp \

HEADERS += \
    ../../neuralnet_predict/NeuralNet.h \
    ../../neuralnet_predict/CSVreader.h \
    


