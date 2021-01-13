cmake_minimum_required(VERSION 3.16)
project(EyeTrackingNext)

include(cmake/CompileDefinitions.cmake)

add_subdirectory(Packages)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Main)