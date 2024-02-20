cmake_minimum_required(VERSION 3.22)
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
        source/common_emitter.cpp
        include/resistor.h
        source/resistor.cpp include/capacitor.h source/capacitor.cpp include/filter.h source/filter.cpp include/collector_feedback.h source/collector_feedback.cpp source/high_pass.cpp include/high_pass.h source/low_pass.cpp include/low_pass.h source/band_pass.cpp include/band_pass.h)
