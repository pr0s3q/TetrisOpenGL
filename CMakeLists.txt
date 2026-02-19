cmake_minimum_required(VERSION 3.28)
project(TetrisCMake)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -mavx2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -mavx2")

add_subdirectory(Engine)
add_subdirectory(TetrisOpenGL)