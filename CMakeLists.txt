cmake_minimum_required(VERSION 3.27)
project(TransistorAmplifierCalculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(TransistorAmplifierCalculator source/main.cpp
        include/manager.h
        source/manager.cpp
        include/transistor.h
        source/transistor.cpp
        source/bjt.cpp
        include/bjt.h
        include/circuit.h
        include/common_emitter.h
        source/circuit.cpp
        source/common_emitter.cpp)
