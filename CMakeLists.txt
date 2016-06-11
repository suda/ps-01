cmake_minimum_required(VERSION 3.2)
project(ps_01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/synth/fastsid_synth_engine.h
    src/synth/synth.cpp
    src/synth/synth.h
    src/synth/synth_engine.h
    src/synth/voice.h
    src/application.cpp)

add_executable(ps_01 ${SOURCE_FILES})