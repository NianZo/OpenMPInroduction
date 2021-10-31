cmake_minimum_required(VERSION 3.15)

project(OpenMPIntroduction)

# set_property(TARGET tgt PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

# Standard compiler warnings
add_library(project_warnings INTERFACE)
include(CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# Hello world application
add_subdirectory(HelloWorld)

# Integrate 4 / (1+x^2) from 0 to 1
add_subdirectory(IntegrateToPi)

# Integrate 4 / (1+x^2) from 0 to 1 using OpenMP loop constructs and reductions
add_subdirectory(IntegrateToPiWithLoops)

# Exercise to fix buggy mandelbrot program
add_subdirectory(MandelbrotDebug)
