cmake_minimum_required(VERSION 3.0)

project(plaincpp)
SET(CMAKE_CXX_FLAGS -pthread)
file(GLOB SOURCES
    ./*.cpp
    ./*.h
    )
add_executable(${PROJECT_NAME} ${SOURCES})
