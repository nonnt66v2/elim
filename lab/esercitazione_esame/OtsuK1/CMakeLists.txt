######## A simple cmakelists.txt file for OpenCV() #############  
cmake_minimum_required(VERSION 3.5)
PROJECT(Otsu)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(Otsu main.cpp)
TARGET_LINK_LIBRARIES (Otsu ${OpenCV_LIBS})
########### end ####################################  
