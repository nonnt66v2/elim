cmake_minimum_required(VERSION 3.5)
PROJECT(sobel)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(sobel main.cpp
        main.cpp)
TARGET_LINK_LIBRARIES (sobel ${OpenCV_LIBS})