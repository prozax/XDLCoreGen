cmake_minimum_required(VERSION 3.3)
project(XDLCoreGen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Slicel.cpp Slicel.h Slicem.cpp Slicem.h Slicex.cpp Slicex.h Slice.cpp Slice.h QuarterSlicel.cpp QuarterSlicel.h Module.cpp Module.h Net.cpp Net.h Design.cpp Design.h Port.cpp Port.h Device.cpp Device.h Tile.cpp Tile.h PrimitiveSite.cpp PrimitiveSite.h Multiplier.cpp Multiplier.h IOB.cpp IOB.h Pin.cpp Pin.h)
add_executable(XDLCoreGen ${SOURCE_FILES})