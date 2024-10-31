######## A simple cmakelists.txt file for OpenCV() #############  
cmake_minimum_required(VERSION 3.5)
PROJECT(correlazione)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(correlazione main.cpp)
TARGET_LINK_LIBRARIES (correlazione ${OpenCV_LIBS})
########### end ################