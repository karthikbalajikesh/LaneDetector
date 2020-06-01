# This is a project to identify lanes using a mat frame.
########### 1. Specify CMAKE ################3
cmake_minimum_required(VERSION 3.5.1)

########### 2. Name the Project #############
project(LaneDetector)

########### 3. Set Compiler Settings ##########
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_BUILD_TYPE Debug)

########### 4. Adding Dependency #################

# this project is only going to find lanes using
# a stream of video or webcam. Hence we need opencv

set(OpenCV_Dir "/home/karthik/opencv4/installation/OpenCV-master/lib/cmake/opencv4")
set(CMAKE_PREFIX_PATH "${OpenCV_Dir};${CMAKE_PREFIX_PATH}")

find_package(OpenCV 4.3.0)

########### 5. setting libraries and source ###########################
set(LIBS "${OpenCV_LIBS}")
FILE(GLOB SOURCES "./src/*.cpp")
include_directories(include)

########### 6. Creating Libraries ##########################
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../lib")
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

########### 7. Adding test files  ##########################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
FILE(GLOB CUSTOMLIBS lib/*)
set(LIBS ${CUSTOMLIBS};${LIBS})
# 1. example.cpp
add_executable(example "test/example.cpp")
target_link_libraries(example ${LIBS})
