cmake_minimum_required(VERSION 3.10)

project(producer_consumer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_BUILD_TYPE Debug)

set(SOURCES
    main.cpp
    Queue.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
