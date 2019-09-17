cmake_minimum_required(VERSION 2.8)

project(Primer)
file(GLOB SOURCES
    ./*.cpp
    ./*.h)

add_executable(${PROJECT_NAME} ${SOURCES})
