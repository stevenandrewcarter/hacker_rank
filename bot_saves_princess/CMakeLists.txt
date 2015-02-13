cmake_minimum_required(VERSION 2.8.4)
project(bot_saves_princess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(bot_saves_princess ${SOURCE_FILES})