######## A simple cmakelists.txt file for OpenCV() #############  
cmake_minimum_required(VERSION 3.5)
PROJECT(Otsu_2)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(Otsu_2 main.cpp)
TARGET_LINK_LIBRARIES (Otsu_2 ${OpenCV_LIBS})
########### end ####################################  
