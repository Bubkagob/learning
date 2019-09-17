cmake_minimum_required(VERSION 2.8)

project(vcClient)
file(GLOB SOURCES
    ./*.cpp
    ./*.h)

FIND_PACKAGE(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} "${CMAKE_THREAD_LIBS_INIT}")
