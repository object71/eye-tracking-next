cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(EyeTrackingNext)

include(cmake/CompileDefinitions.cmake)

find_package(OpenCV CONFIG REQUIRED)
find_package(Python3 COMPONENTS Interpreter)
add_subdirectory(Packages)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Main)