cmake_minimum_required(VERSION 2.8)

project(CancelAsyncOper)
file(GLOB SOURCES
    ./*.h
    ./*.cpp)
FIND_PACKAGE(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} "${CMAKE_THREAD_LIBS_INIT}")
