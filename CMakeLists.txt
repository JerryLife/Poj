cmake_minimum_required(VERSION 3.9)
project(Poj)

set(CMAKE_CXX_STANDARD 98)

set(BUILD Parity-Game)
set(SOURCE_FILES Parity-Game.cpp)
add_executable(${BUILD} ${SOURCE_FILES})

set(BUILD Food-Chain)
set(SOURCE_FILES Food-Chain.cpp True-Liars.cpp)
add_executable(${BUILD} ${SOURCE_FILES})

set(BUILD Test)
set(SOURCE_FILES Test.cpp)
add_executable(${BUILD} ${SOURCE_FILES})