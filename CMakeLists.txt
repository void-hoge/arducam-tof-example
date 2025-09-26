cmake_minimum_required(VERSION 3.20)

project(arducam-tof-example)

find_package(ArducamDepthCamera REQUIRED)

set(CXXLIBS ArducamDepthCamera::ArducamDepthCamera)

add_subdirectory(src)
