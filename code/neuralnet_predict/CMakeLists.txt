cmake_minimum_required(VERSION 3.10)

project(run)
add_executable(run main.cpp NeuralNet.cpp CSVreader.cpp)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(SYSTEM ${NNPACK_INCLUDE_DIR})
include_directories(.)
