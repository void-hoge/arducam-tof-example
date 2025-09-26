cmake_minimum_required(VERSION 3.20)

project(arducam-tof-example)

find_package(ArducamDepthCamera REQUIRED)

add_executable(capture main.cpp)

target_link_libraries(capture ArducamDepthCamera::ArducamDepthCamera)

target_compile_options(capture PUBLIC -O3 -mtune=native -march=native)
