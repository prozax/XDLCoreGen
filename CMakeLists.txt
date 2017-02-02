cmake_minimum_required(VERSION 3.3)
project(XDLCoreGen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Slicel.cpp Slicel.h Slicem.cpp Slicem.h Slicex.cpp Slicex.h Slice.cpp Slice.h QuarterSlicel.cpp QuarterSlicel.h AddSub.cpp AddSub.h)
add_executable(XDLCoreGen ${SOURCE_FILES})