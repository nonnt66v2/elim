cmake_minimum_required(VERSION 3.5)
PROJECT(laplaciano)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(laplaciano main.cpp)
TARGET_LINK_LIBRARIES (laplaciano ${OpenCV_LIBS})