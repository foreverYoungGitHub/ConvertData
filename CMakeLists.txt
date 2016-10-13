cmake_minimum_required(VERSION 3.6)
project(ConvertData)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(OpenCV_DIR "/usr/local/lib")
find_package(OpenCV)

find_package( Boost  COMPONENTS system filesystem REQUIRED )
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})


set(SOURCE_FILES main.cpp ConvertData.cpp ConvertData.h DeletePath.cpp DeletePath.h)
add_executable(ConvertData ${SOURCE_FILES})

target_link_libraries(ConvertData ${OpenCV_LIBS} )
target_link_libraries( ConvertData ${Boost_LIBRARIES} )