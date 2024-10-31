######## A simple cmakelists.txt file for OpenCV() #############  
cmake_minimum_required(VERSION 3.5)
PROJECT(SPM)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(SPM main.cpp)
TARGET_LINK_LIBRARIES (SPM ${OpenCV_LIBS})
########### end ####################################  
