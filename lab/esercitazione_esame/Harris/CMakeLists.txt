######## A simple cmakelists.txt file for OpenCV() #############
cmake_minimum_required(VERSION 3.5)
PROJECT(Harris)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(Harris main.cpp)
TARGET_LINK_LIBRARIES (Harris ${OpenCV_LIBS})