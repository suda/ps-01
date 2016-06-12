cmake_minimum_required(VERSION 3.5)
project(ps_01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/synth/sound_output.h
    src/synth/synth.cpp
    src/synth/synth.h
    src/synth/voice.h
    src/application.cpp src/synth/dac_sound_output.cpp src/synth/dac_sound_output.h src/synth/file_sound_output.cpp src/synth/file_sound_output.h)

add_executable(ps_01 ${SOURCE_FILES})