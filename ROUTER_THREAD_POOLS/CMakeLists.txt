cmake_minimum_required(VERSION 3.10)

project(router VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_BUILD_TYPE Debug)

set(SOURCES
    main.cpp
    Router.cpp
    Device.cpp
    MessageBus.cpp
    ThreadPool.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
