######## A simple cmakelists.txt file for OpenCV() #############  
cmake_minimum_required(VERSION 3.5)
PROJECT(es_3)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(es_3 kmeansColor.cpp)
TARGET_LINK_LIBRARIES (es_3 ${OpenCV_LIBS})
########### end ####################################  
