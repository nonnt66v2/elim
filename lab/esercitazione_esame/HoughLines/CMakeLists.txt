######## A simple cmakelists.txt file for OpenCV() #############  
cmake_minimum_required(VERSION 3.5)
PROJECT(Hough)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(Hough main.cpp)
TARGET_LINK_LIBRARIES (Hough ${OpenCV_LIBS})
########### end ####################################  
