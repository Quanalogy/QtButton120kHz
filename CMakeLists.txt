cmake_minimum_required(VERSION 3.5)
project(QtButton120kHz)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

set(SOURCE_FILES main.cpp Send120kHz.cpp Send120kHz.h)
add_executable(QtButton120kHz ${SOURCE_FILES})
target_link_libraries(QtButton120kHz Qt5::Core Qt5::Widgets Qt5::Gui)