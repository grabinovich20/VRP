cmake_minimum_required(VERSION 3.0)
project(VRP)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the directory containing header files
include_directories(src)

# Add all the source files
set(SOURCES 
    src/input.cpp
    src/main.cpp
    src/graph.cpp
)

# Add an executable target
add_executable(VRP ${SOURCES})
