cmake_minimum_required(VERSION 3.0)
project(your_project)

find_package(OpenCV REQUIRED)

add_executable(your_program main.cpp)
target_link_libraries(your_program ${OpenCV_LIBS})

