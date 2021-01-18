cmake_minimum_required(VERSION 3.16)
project(EyeTrackingNext)

option(PROFILE_APP "Enable profiling on the executable" ON)

include(cmake/CompileDefinitions.cmake)


find_package(OpenCV CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)
add_subdirectory(Packages)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(DataGen)
add_subdirectory(Main)

add_custom_target(DataGenRun
                  COMMAND DataGen "${CMAKE_CURRENT_SOURCE_DIR}" "${Main_BINARY_DIR}"
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  COMMENT "Executing data generation app"
                  SOURCES ${DataGenSources}
                  )

add_dependencies(Main DataGenRun)
