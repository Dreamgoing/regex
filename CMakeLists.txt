cmake_minimum_required(VERSION 3.6)
project(regex)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test.cpp DFA.cpp DFA.h
        NFA.cpp NFA.h State.cpp State.h Transition.cpp Transition.h Regex.cpp Regex.h)
add_executable(tes ${SOURCE_FILES})