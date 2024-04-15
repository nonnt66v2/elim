#scrivi cmakelist per opencv
cmake_minimum_required(VERSION 3.5)
PROJECT(es_4)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(es_4 main.cpp)
TARGET_LINK_LIBRARIES (es_4 ${OpenCV_LIBS})
