cmake_minimum_required(VERSION 3.5)

project(lab3)

add_executable(lab3
  main.cpp
  figure.cpp
  myvector.cpp
  point.cpp
  octagon.cpp
  square.cpp
  triangle.cpp
)

set_property(TARGET lab3 PROPERTY CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")