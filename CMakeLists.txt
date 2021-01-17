cmake_minimum_required(VERSION 3.16)
project(EyeTrackingNext)

include(cmake/CompileDefinitions.cmake)

find_package(OpenCV CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Python3 COMPONENTS Interpreter)
add_subdirectory(Packages)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Main)