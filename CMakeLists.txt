cmake_minimum_required(VERSION 3.5)
project(ps_01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

AUX_SOURCE_DIRECTORY(src/synth SOURCE_FILES)
AUX_SOURCE_DIRECTORY(src/vendor SOURCE_FILES)

list(APPEND
    SOURCE_FILES
    src/application.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(ps_01 ${SOURCE_FILES})

target_link_libraries(ps_01 ${SDL2_LIBRARIES})