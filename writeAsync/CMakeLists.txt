cmake_minimum_required(VERSION 3.0)

project(writeAsync)
file(GLOB SOURCES
    ./*.h
    ./*.cpp)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(Boost REQUIRED COMPONENTS system)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} "${CMAKE_THREAD_LIBS_INIT}")
