cmake_minimum_required(VERSION 2.8)
project(Robot)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -pedantic -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -I${CMAKE_CURRENT_LIST_DIR}/wpilib/include/ -I${CMAKE_CURRENT_LIST_DIR}/src -I${CMAKE_CURRENT_LIST_DIR}/CTRE/include -I${CMAKE_CURRENT_LIST_DIR}/wpilib/lib -O0 -g3 -fmessage-length=0 -flto=1 -Wno-error --param ggc-min-expand=0")
SET(CMAKE_EXE_LINKER_FLAGS "-L${CMAKE_CURRENT_LIST_DIR}/wpilib/lib -L${CMAKE_CURRENT_LIST_DIR}/bin/libpathfinder -Wl,-rpath,/opt/GenICam_v2_3/bin/Linux_armv7-a")

#including other libraries
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/ADIS16448-RoboRIO-Driver/C++/include")
#are these necessary?
include_directories("${CMAKE_CURRENT_LIST_DIR}/wpilib/include/")
include_directories(${CMAKE_CURRENT_LIST_DIR}/CTRE/include/)

file(GLOB_RECURSE COM_SRC_FILES src/*.cpp lib/*.cpp)
#add_subdirectory(hal)
#add_subdirectory(networktables/cpp)
#add_subdirectory(wpilibc)
ADD_EXECUTABLE(FRC ${COM_SRC_FILES})
ADD_LIBRARY(TalonSRXLib STATIC IMPORTED)
SET_TARGET_PROPERTIES(TalonSRXLib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/CTRE/lib/libTalonSRXLib.a)
TARGET_LINK_LIBRARIES(FRC TalonSRXLib wpi)
