cmake_minimum_required(VERSION 3.17)
project(bf)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
        src/**/*.cpp
        src/**/*.h
        src/*.cpp
        src/*.h
)

add_executable(bf ${SOURCES})
