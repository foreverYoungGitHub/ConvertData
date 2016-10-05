cmake_minimum_required(VERSION 3.6)
project(ConvertData)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ConvertData.cpp ConvertData.h)
add_executable(ConvertData ${SOURCE_FILES})